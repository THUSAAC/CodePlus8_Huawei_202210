#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb emplace_back
#define pf emplace_front
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 18 + 2;
int n,m,k,q;
int a[MAXN],b[MAXN];

struct Node{
	int x,y;
	Node(int x=0,int y=0) : x(x),y(y) {}

	bool operator < (const Node &t) const {
		if(x != t.x) return x < t.x;
		return y > t.y;
	}
}f[6718464+2333];

void upd(Node &x,Node y){
	if(y < x) x = y;
}

Node gao(Node v,int hp){
	if(hp <= 0) return v;
	if(v.x == k+1) return v;
	while(v.x <= k && v.y < hp){
		v.x++;
		v.y = b[v.x];
	}
	if(v.x == k+1) return v;
	v.y -= hp;
	return v;
}

int mp[MAXN],ext[MAXN];
int di1[MAXN],di2[MAXN],id[MAXN];
int t1,t2;
int pw[MAXN];

int get(int S1,int S2){
	return S1*pw[t2]+S2;
}

std::vector<int> vec;

int main(){
//	freopen("a.in","r",stdin);
	scanf("%d%d%d%d",&n,&m,&k,&q);
	pw[0] = 1;FOR(i,1,10) pw[i] = pw[i-1]*3;
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);--u;--v;
		mp[u] |= 1<<v;mp[v] |= 1<<u;
	}
	FOR(i,0,n-1) scanf("%d",a+i);
	FOR(i,1,k) scanf("%d",b+i);
	CLR(ext,-1);
	FOR(i,1,q){
		int c,d;scanf("%d%d",&c,&d);--c;
		di2[t2++] = c;id[c] = t2-1;ext[c] = d;
	}
	FOR(i,0,n-1) if(ext[i] == -1) di1[t1++] = i,id[i] = t1-1;
	int all = get((1<<t1)-1,pw[t2]-1);
	FOR(S,0,all) f[S].x = k+1;
	FOR(i,0,n-1){
		if(ext[i] == -1) f[get(1<<id[i],0)] = gao(Node(1,b[1]),a[i]);
		else f[get(0,pw[id[i]])] = gao(Node(1,b[1]),a[i]);
	}
	FOR(S,1,all){
		if(f[S].x == k+1) continue;
		int S1 = S/pw[t2],S2 = S%pw[t2],nd = 0;
		FOR(i,0,t1-1) if((S1>>i)&1) nd |= 1<<di1[i];
		FOR(i,0,t2-1){
			int t = (S2/pw[i])%3;
			nd |= (t != 0)<<di2[i];
			if(t == 1) vec.pb(di2[i]);
		}
		vec.clear();
		FOR(i,0,t2-1) if((S2/pw[i])%3 == 1) vec.pb(di2[i]);
		FOR(v,0,n-1){
			if((nd>>v)&1) continue;
			if(!(mp[v]&nd)) continue;
			int nS1 = S1,nS2 = S2;
			if(ext[v] == -1){
				nS1 |= (1<<id[v]);
			}
			else{
				nS2 += pw[id[v]];
			}
			upd(f[get(nS1,nS2)],gao(f[S],a[v]));
			for(auto x:vec){
				upd(f[get(nS1,nS2+pw[id[x]])],gao(f[S],a[v]-ext[x]));
			}
		}
		for(auto x:vec) upd(f[get(S1,S2+pw[id[x]])],f[S]);
	}
	if(f[all].x == k+1) puts("FAIL");
	else printf("%d %d\n",f[all].x,f[all].y);
	return 0;
}
