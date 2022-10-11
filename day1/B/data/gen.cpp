#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[10000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define uli unsigned li
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
//const int mo = 998244353;
//const int mo = 1000000007;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(int d){
	cerr<<d<<":"<<endl;
	char c[50];
	sprintf(c,"%d.in",d);
	//freopen(c,"r",stdin);
	//sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
inline void file2(int d){
	char c[50];
	sprintf(c,"b <%d.in >%d.ans",d,d);
	//freopen(c,"r",stdin);
	//sprintf(c,"%s.out",s);
	//freopen(c,"w",stdout);
	system(c);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(li mo = 998244853){
	srd = (srd * s1 + s2 + rand()) % s3;
	return srd % mo;// % 100;
}
int n,m,mm,k,q,a[20],b[20],c[20],d[20],x[210],y[210];
bool vis[20];
int f[20];
int e[20][20];
inline int getf(int x){return f[x] == x ? x : f[x] = getf(f[x]);}
inline void mg(int u,int v){f[getf(u)] = getf(v);} 
inline void init(){for(int i = 1;i <= n;++i) f[i] = i;}
inline bool chk(){
	for(int i = 2;i <= n;++i) if(getf(i) != getf(1)) return 0;
	return 1;
}
inline void add(int u,int v){
	if(u == v || e[u][v]) return;
	e[u][v] = e[v][u] = 1;
	x[++mm] = u;y[mm] = v;
	mg(u,v);
}
inline void ini(){
	n = m = mm = k = q = 0;
	#define clr(x) memset(x,0,sizeof(x))
	clr(a);clr(b);clr(c);clr(d);clr(x);clr(y);clr(vis);clr(f);clr(e);
	#undef clr
} 
int nn[] = {5,8,12,12,18,18,18,18,18},qq[] = {5,8,0,8,0,8,8,8,8};
inline void gen(int id){
	file(id);ini();
	int i,j,l,g,h;
	//n = rd() % 5 + 14;
	int tsd = (id - 1) / 3;
	n = nn[tsd] - rd() % 2;
	m = rd() % (n * (n - 1) / 2 + 1);
	if(tsd == 7) m = n * (n - 1) / 2;
	init();for(i = 1;i <= m;++i) add(rd() % n + 1,rd() % n + 1);
	while(!chk() || (tsd == 7 && mm < m)) add(rd() % n + 1,rd() % n + 1);
	m = mm;
	k = rd() % n + 1;
	if(tsd == 5) k = 1;
	q = max(0ll,min(1ll * n,qq[tsd] - rd() % 2));
	cerr<<n<<" "<<m<<" "<<k<<" "<<q<<endl;
	for(i = 1;i <= n;++i) a[i] = (rd(tsd == 6 ? 10 : s3) >> (k == 1 ? 3 : k <= 3 ? 2 : 1)) + 1;
	for(i = 1;i <= k;++i) b[i] = rd(tsd == 6 ? 10 : s3) + 1;
	for(i = 1;i <= q;++i){
		g = rd() % n + 1;
		while(vis[g]) g = rd() % n + 1;
		vis[g] = 1;
		h = (rd(tsd == 6 ? 10 : s3) >> 2) + 1;
		c[i] = g;d[i] = h;
	}
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	for(i = 1;i <= m;++i) print(x[i]),pc(' '),print(y[i]),pc('\n');
	for(i = 1;i <= n;++i) print(a[i]),pc(' ');pc('\n');
	for(i = 1;i <= k;++i) print(b[i]),pc(' ');pc('\n');
	for(i = 1;i <= q;++i) print(c[i]),pc(' '),print(d[i]),pc('\n');
	cerr<<"***"<<endl;
	file2(id); 
}
int main(){
	srand(time(0));rd();
	//file("");
	int tsd = read();
	if(tsd) gen(tsd);
	else for(tsd = 1;tsd <= 27;++tsd) gen(tsd); 
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
