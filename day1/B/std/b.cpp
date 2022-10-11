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
int n,m,k,q,a[20],b[20],e[20],d[20];
int dj[20][2],bas[20],bs[20],bh[20];
int to1[7000010],to2[7000010],ee[7000010];
int lgo[300010];
pii f[7000010];
int wq[20][20][20],xie[20][20],lft[20][20][20];
inline pii upd(pii x,pii y){
	return x.fi == y.fi ? (x.se > y.se ? x : y) : (x.fi < y.fi ? x : y);
}
inline void dfs(int o,int u,int x,int y){
	if(o == n + 1){
		//assert(to1[u] == x && to2[u] == y);
		//cerr<<u<<":"<<to1[u]<<" "<<to2[u]<<" "<<x<<" "<<y<<endl;
		to1[u] = x;
		to2[u] = y;
		return;
	}
	for(int i = 0;i < (d[o] ? 3 : 2);++i){
		int tx = x,ty = y;
		if(i) tx |= 1 << o - 1;
		if(i == 1 && d[o]) ty |= 1 << bh[o] - 1;
		dfs(o + 1,u + i * bas[o],tx,ty);
	}
}
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,l,u,v;
	n = read();m = read();k = read();q = read();
	for(i = 1;i <= m;++i){
		u = read();v = read();
		e[u] |= 1 << v - 1;
		e[v] |= 1 << u - 1;
	}
	for(i = 1;i <= n;++i) a[i] = read();
	for(i = 1;i <= k;++i) b[i] = read();
	for(i = 1;i <= q;++i){
		u = read();v = read();d[u] = v; 
	}
	l = 0;bas[1] = 1;
	for(i = 1;i <= n;++i){
		if(d[i]){
			dj[++l][0] = i;
			dj[l][1] = d[i];
			bas[i + 1] = bas[i] * 3;
			bs[i] = 3;
			bh[i] = l;
		}
		else bas[i + 1] = bas[i] * 2,bs[i] = 2;
	} 
	int tot = bas[n + 1] - 1;
	/*
	for(i = 0;i <= tot;++i){
		l = i;u = 0;v = 0;
		for(j = 1;j <= n;++j){
			if(l % bs[j]) u |= 1 << j - 1;
			if(d[j] && l % bs[j] == 1) v |= 1 << bh[j] - 1; 
			l /= bs[j];
		}
		to1[i] = u;to2[i] = v;
		//cerr<<i<<":"<<to1[i]<<" "<<to2[i]<<" "<<bh[1]<<" "<<bh[2]<<" "<<bh[3]<<endl;
	}
	*/
	dfs(1,0,0,0);
	int tt1 = (1 << n) - 1,tt2 = (1 << q) - 1;
	for(i = 1;i <= tt1;++i) lgo[i] = lgo[i >> 1] + 1;
	for(i = 1;i <= tt1;++i) ee[i] = ee[i & (i - 1)] | e[lgo[i & -i]];
	ee[0] = tt1;
	//for(i = 1;i <= n;++i) cerr<<e[i]<<" ";cerr<<endl; 
	//for(i = 0;i <= tot;++i) cerr<<ee[i]<<" ";cerr<<endl;
	memset(wq,0x3f,sizeof(wq));
	
	for(i = 1;i <= n;++i)
		for(j = 0;j <= q;++j){
		int o = max(a[i] - dj[j][1],0);
		xie[i][j] = o;
		for(u = 1;u <= k;++u){
			for(v = u;v <= k && b[v] < o;++v);
			if(v <= k) wq[i][j][u] = v,lft[i][j][u] = b[v] - o;
			//cerr<<i<<" "<<j<<" "<<u<<":"<<o<<" "<<v<<" "<<b[v] - o<<endl;
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0].fi = f[0].se = 0;
	for(i = 0;i < tot;++i) if(f[i].fi <= k){
		u = to1[i];v = to2[i];
		//cerr<<i<<":"<<u<<" "<<v<<":::"<<f[i].fi<<" "<<f[i].se<<endl;
		for(int o = (tt1 - u) & ee[u];o;o -= o & -o){
			j = lgo[o & -o];
			l = 0;
			int oo = v;
			do{
				int nxt = i + bas[j] + bas[dj[l][0]];
				if(f[i].se >= xie[j][l]){
					//cerr<<f[nxt].fi<<" "<<f[nxt].se<<"   "<<f[i].fi<<" "<<f[i].se - xie[j][l]<<endl;
					f[nxt] = upd(f[nxt],mp(f[i].fi,f[i].se - xie[j][l]));
					//cerr<<f[nxt].fi<<" "<<f[nxt].se<<endl;
				} 
				else f[nxt] = upd(f[nxt],mp(wq[j][l][f[i].fi + 1],lft[j][l][f[i].fi + 1]));
				//cerr<<"	()"<<j<<" "<<l<<" "<<nxt<<" "<<xie[j][l]<<" "<<f[nxt].fi<<" "<<f[nxt].se<<endl;
				l = lgo[oo & -oo];
				oo -= oo & -oo;
				
			}while(l);
		}
	}
	pii ans = f[tot + 1];
	for(i = 0;i <= tot;++i) if(to1[i] == tt1) ans = upd(ans,f[i]);
	if(ans.fi > k) puts("FAIL");
	else print(ans.fi),pc(' '),print(ans.se),pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	cerr<<clock()<<endl;
	return 0;
}
