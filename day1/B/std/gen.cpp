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
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	srd = (srd * s1 + s2 + rand()) % s3;
	return srd;// % 100;
}
int n,m,mm,k,q,a[20],b[20],c[20],d[20],x[210],y[210];
bool vis[20];
int f[20];
inline int getf(int x){return f[x] == x ? x : f[x] = getf(f[x]);}
inline void mg(int u,int v){f[getf(u)] = getf(v);} 
inline void init(){for(int i = 1;i <= n;++i) f[i] = i;}
inline bool chk(){
	for(int i = 2;i <= n;++i) if(getf(i) != getf(1)) return 0;
	return 1;
}
int e[20][20];
inline void add(int u,int v){
	if(u == v || e[u][v]) return;
	e[u][v] = e[v][u] = 1;
	x[++mm] = u;y[mm] = v;
	mg(u,v);
}
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,l,g,h;
	//n = rd() % 5 + 14;
	n = 18;
	m = rd() % (n * (n - 1) / 2 + 1);
	init();for(i = 1;i <= m;++i) add(rd() % n + 1,rd() % n + 1);
	while(!chk()) add(rd() % n + 1,rd() % n + 1);
	m = mm;
	k = rd() % n + 1;
	q = rd() % min(9,n + 1);
	for(i = 1;i <= n;++i) a[i] = (rd() >> 1) + 1;
	for(i = 1;i <= k;++i) b[i] = rd() + 1;
	for(i = 1;i <= q;++i){
		g = rd() % n + 1;
		while(vis[g]) g = rd() % n + 1;
		vis[g] = 1;
		h = (rd() >> 2) + 1;
		c[i] = g;d[i] = h;
	}
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	for(i = 1;i <= m;++i) print(x[i]),pc(' '),print(y[i]),pc('\n');
	for(i = 1;i <= n;++i) print(a[i]),pc(' ');pc('\n');
	for(i = 1;i <= k;++i) print(b[i]),pc(' ');pc('\n');
	for(i = 1;i <= q;++i) print(c[i]),pc(' '),print(d[i]),pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


