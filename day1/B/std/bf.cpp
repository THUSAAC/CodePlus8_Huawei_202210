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
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,k,q,e[20][20];
int a[20],b[20],c[20],d[20];
bool vis1[20],vis2[20];
pii ans = mp(21,0);
inline void ud(int x,int y){
	if(x < ans.fi) ans = mp(x,y);
	else if(x == ans.fi && y > ans.se) ans = mp(x,y); 
}
inline bool chk(int x){
	if(vis1[x]) return 0;
	for(int i = 1;i <= n;++i) if(vis1[i] && e[i][x]) return 1;
	return 0;
}
inline void chknxt(int x,int y,int &tox,int &toy,int v){
	if(y >= v){
		tox = x;toy = y - v;return;
	}
	tox = k + 1;
	for(int i = x + 1;i <= k;++i) if(b[i] >= v){
		tox = i;toy = b[i] - v;return;
	}
}
inline void dfs(int nw,int x,int y){
	if(x > k) return;
	if(nw == n + 1){
		ud(x,y);
		return;
	}
	for(int i = 1;i <= n;++i) if(nw == 1 || chk(i)){
		int tox = 0,toy = 0;
		chknxt(x,y,tox,toy,a[i]);
		if(tox <= k){
			vis1[i] = 1;
			dfs(nw + 1,tox,toy);
			vis1[i] = 0;
		}
		for(int j = 1;j <= q;++j) if(vis1[c[j]] && !vis2[j]){
			chknxt(x,y,tox,toy,max(0,a[i] - d[j]));
			if(tox > k) continue;
			vis1[i] = vis2[j] = 1;
			dfs(nw + 1,tox,toy);
			vis1[i] = vis2[j] = 0;
		}
	}
}
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,l,u,v;
	n = read();m = read();k = read();q = read();
	for(i = 1;i <= m;++i){
		u = read();v = read();
		e[u][v] = e[v][u] = 1;
	}
	for(i = 1;i <= n;++i) a[i] = read();
	for(i = 1;i <= k;++i) b[i] = read();
	for(i = 1;i <= q;++i) c[i] = read(),d[i] = read();
	dfs(1,0,0);
	if(ans.fi > k) puts("FAIL");
	else print(ans.fi),pc(' '),print(ans.se),pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


