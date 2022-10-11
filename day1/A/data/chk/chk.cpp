//This is a chk avoiding spaces at each end of a line and \n at end of the file
//You can include .h file like testlib.h here
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cassert>

FILE *inFile;
FILE *outFile;
FILE *ansFile;
FILE *scoreFile;
FILE *infoFile;
double score;
bool swap_flag;
std::ostringstream info;

const char esc[][5] = {
	"\\0", "\\x01", "\\x02", "\\x03", "\\x04", "\\x05", "\\x06", "\\a",
	"\\b", "\t", "\\n", "\v", "\\f", "\\r", "\\x0e", "\\x0f",
	"\\x10", "\\x11", "\\x12", "\\x13", "\\x14", "\\x15", "\\x16", "\\x17",
	"\\x18", "\\x19", "\\x1a", "\\x1b", "\\x1c", "\\x1d", "\\x1e", "\\x1f"
};
const int CONTEXT_LEN = 10;

bool blank(char c){
	return c == ' ' || c == '\t' || c == '\r';
}

struct Reader{
	int ptr, len, line, col;
	bool eof, first;
	FILE *file;
	char buff[CONTEXT_LEN * 3 + 11];
	void fresh(){
		if(!eof && len - ptr < CONTEXT_LEN + 1){
			int lef = std::max(ptr - CONTEXT_LEN, 0);
			int rig = std::min(len, ptr + CONTEXT_LEN * 2 + 1);
			for(int i = lef, j = 0; i <= rig; i++, j++)
				buff[j] = buff[i];
			ptr -= lef;
			len = rig - lef;
			for(int end = ptr + CONTEXT_LEN * 2 + 2; len < end;){
				char c = fgetc(file);
				if(c == EOF){
					eof = true;
					break;
				}
				buff[len++] = c;
			}
			buff[len] = 0;
			first = false;
		}
		if(!line){
			line = 1;
			first = true;
			col++;
		}
	}
	char cur(){
		fresh();
		return buff[ptr];
	}
	char next(){
		if(buff[ptr] == '\n'){
			line++;
			col = 0;
		}
		if(buff[ptr]){
			ptr++;
			col++;
		}
		fresh();
		return buff[ptr];
	}
	bool rest_empty(){
		for(; blank(cur()) || cur() == '\n'; next());
		return !cur();
	}
}inf,outf, ansf;

std::ostream& operator<<(std::ostream& ost, const Reader& r){
	int lef = std::max(r.ptr - CONTEXT_LEN, 0);
	int rig = std::min(r.ptr + CONTEXT_LEN + 1, r.len);
	if(!r.first || lef != 0)
		ost << "...";
	for(int i = lef; i < rig; i++){
		//Arbiter cannot print {} in info
		if(i == r.ptr)
			ost << (swap_flag ? '[' : '{');
		if(r.buff[i] >= 0 && r.buff[i] < 32)
			ost << esc[r.buff[i]];
		else if(swap_flag && r.buff[i] == '{')
			ost << "\\[";
		else if(swap_flag && r.buff[i] == '}')
			ost << "\\]";
		else
			ost << r.buff[i];
		if(i == r.ptr)
			ost << (swap_flag ? ']' : '}');;
	}
	if(!r.eof || rig != r.len)
		ost << "...";
	return ost;
}

long long sum[4],a[200003];
char sym[4]={0,'B','Y','Z'};
int n;

void ret(double result, int add_context,char qwq=0){
	if(add_context)
	{
		if(swap_flag)
		{
			info.str("Wrong answer.");
			//info in arbiter must shorter than about 100
		}
		if(add_context==1)
		{
			info << "Unexpected char '" << qwq << "' found in output";
		}
		else if(add_context==2)
		{
			info << "total weight of player " << qwq << " exceeds the limit";
		}
		else if(add_context==3)
		{
			info << "Jury has no solution but you have found one";
		}
	}
	/*
	if(add_context)
		if(swap_flag){
			//info in arbiter must shorter than about 100
			info.str("Wrong answer.");
			info << "out:[" << outf << "]@r" << outf.line << "c" << outf.col <<",";
			info << "ans:[" << ansf << "]@r" << ansf.line << "c" << ansf.col <<".";
		}else{
			info << "out: [" << outf << "] at line " << outf.line << ", column " << outf.col <<".\n";
			info << "ans: [" << ansf << "] at line " << ansf.line << ", column " << ansf.col <<".\n";
		}
	*/
	if(swap_flag){
		//Arbiter only allow to read EXACTLY one line info, no less and no more, and must BEFORE score
		std::string st = info.str();
		const char* p = st.data();
		//info in arbiter must shorter than about 100
		for(int i = 0; *p && i < 100; p++, i++)
			if(*p < 0 || *p >= 32)
				fputc(*p, infoFile);
			else
				fprintf(infoFile, esc[*p]);
		fputc('\n', infoFile);
	}
	fprintf(scoreFile, "%.6f\n", result * score);
	if(!swap_flag)
		fprintf(infoFile, "%s\n", info.str().data());
	exit(0);
}

int readint() //input must be legal!
{
	int ret = 0;
	while(blank(inf.cur())||inf.cur()=='\n') {inf.next();}
	while(inf.cur()>='0'&&inf.cur()<='9') {ret = ret*10+inf.cur()-'0'; inf.next();}
	return ret;
}

int main(int argc, char **argv){
	//You'd better not change this swith block
	switch(argc){
		case 0: case 1:		//LOJ and debug
			inFile = fopen("input", "r");
			outFile = fopen("user_out", "r");
			ansFile = fopen("answer", "r");
			scoreFile = stdout;
			infoFile = stderr;
			score = 100;
			break;
		case 4:		//Arbiter
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			scoreFile = infoFile = fopen("/tmp/_eval.score", "w");
			score = 10;
			swap_flag = true;
			break;
		case 5:
			if(strcmp(argv[4], "THUOJ") == 0){	//Tsinghua OJ(OJ for DSA course)
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[3], "r");
				ansFile = fopen(argv[2], "r");
				scoreFile = stdout;
				infoFile = stdout;
				score = 100;
			}else{								//Tsinsen OJ
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[2], "r");
				ansFile = fopen(argv[3], "r");
				scoreFile = fopen(argv[4], "w");
				infoFile = fopen("tmp", "w");		//Tsinsen doesn't use this file
				score = 1;
			}
			break;
		case 7:		//Lemon and TUOJ
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			FILE *fs = fopen(argv[4], "r");
			if(fs)
				fscanf(fs, "%lf", &score);		//Current TUOJ
			else
				sscanf(argv[4], "%lf", &score);	//Lemon and future TUOJ
			scoreFile = fopen(argv[5], "w");
			infoFile = fopen(argv[6], "w");
			break;
	}
	inf.file = inFile;
	outf.file = outFile;
	ansf.file = ansFile;
	/*
	while(true){
		ansf.next();
		outf.next();
		if(ansf.cur() == '\n')
			for(; blank(outf.cur()); outf.next());
		if(outf.cur() == '\n')
			for(; blank(ansf.cur()); ansf.next());
		if(!outf.cur() || !ansf.cur())
			break;
		if(ansf.cur() != outf.cur()){
			info << "Your output is different from the answer.\n";
			ret(0);
		}
	}
	if(!outf.cur() && !ansf.rest_empty()){
		info << "The answer is longer than your output.\n";
		ret(0);
	}
	if(!ansf.cur() && !outf.rest_empty()){
		info << "Your output is longer than the answer. \n";
		ret(0);
	}
	*/
	n = readint();
	for(int i=1; i<=n; i++)
	{
		a[i] = readint();
		sum[0] += a[i];
	}
	ansf.next(); outf.next();
	if(ansf.cur()=='I')
	{
		while(true){
			if(!ansf.cur()||ansf.cur()=='\n'||blank(ansf.cur()))
				break;
			if(ansf.cur()!=outf.cur()){
				ret(0,3);
			}
			ansf.next();
			outf.next();
		}
		while(outf.cur())
		{
			if(outf.cur()=='\n'||blank(outf.cur())) {outf.next();}
			else
			{
				ret(0,1,outf.cur());
			}
		}
	}
	else
	{
		for(int i=1; i<=n; i++)
		{
			char x = outf.cur();
			if(x=='B') {sum[1]++;}
			else if(x=='Y') {sum[2]++;}
			else if(x=='Z') {sum[3]++;}
			else {ret(0,1,x);}
			outf.next();
		}
		while(outf.cur())
		{
			if(outf.cur()=='\n'||blank(outf.cur())) {outf.next();}
			else
			{
				ret(0,1,outf.cur());
			}
		}
		for(int i=1; i<=3; i++)
		{
			if(sum[i]*2ll>=sum[0])
			{
				ret(0,2,sym[i]);
			}
		}
	}

	info << "Correct.";
	ret(1, 0);
	
	return 0;
}
