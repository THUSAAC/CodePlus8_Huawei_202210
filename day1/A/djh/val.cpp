#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
inline li read(li l = 0,li r = 1e9){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9'){
		assert(y != '-' && (c == ' ' || c == '\n' || c == '\r' || c == '-'));
		y = c;c = gc;
	} 
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	assert(c == -1 || c == ' ' || c == '\n' || c == '\r');
	if(y == '-') x *= -1;
	assert(x >= l && x <= r);
	return x;
}
void end_chk(){
	char c;
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
}
int n,m;

void test(int id, int Nl, int Nr, int al, int ar) {
		char ch[50];
		sprintf(ch,"%d.in",id);
		freopen(ch,"r",stdin);
		n = read(Nl, Nr);
    if(ar == -1) ar = n;
		for(int i = 1;i <= n;++i) read(al, ar);
		end_chk();
		fclose(stdin); 
}

void testok(int id) {
  char ch[50];
  sprintf(ch, "%d.ans", id);
  freopen(ch, "r", stdin);
  string s;
  cin >> s;
  assert(s != "Internationale!");
  end_chk();
  fclose(stdin);
} 

int main(int argc, char** argv){
	int tot = 4;
	for(int tsd = 1;tsd <= tot;++tsd){
    test(tsd, 3, 3, 1, 1000000000);
	}
  for(int tsd = 1; tsd <= 13; ++tsd) {
    test(tsd, 3, 16, 1, 1000000000);
  }
  for(int tsd = 14; tsd <= 19; ++tsd) {
    test(tsd, 3, 1000, 1, -1);
  }
  for(int tsd = 1; tsd <= 26; ++tsd) {
    test(tsd, 3, 200000, 1, 1000000000);
  }
  vector<int> test4 = [1,3,4,5,8,9,10,12,13,15,17,18,19,20,21,22,23,24,25];
  for(int tsd : test4) {
    test(tsd, 3, 200000, 1, 1000000000);
    testok(tsd);
  }
	return 0;
}
