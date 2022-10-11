#include "testlib.h"
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

int n;
bool vis[233];
bool mp[233][233];
bool vis2[233];int tot;

void dfs(int v){
	vis2[v] = 1;++tot;
	FOR(i,1,n) if(mp[v][i] && !vis2[i]) dfs(i);
}

int main(int argc,char *argv[]){
	registerValidation(argc,argv);

	n = inf.readInt(1,12,"n");
	inf.readSpace();
	int m = inf.readInt(n-1,n*(n-1)/2,"m");
	inf.readSpace();
	int k = inf.readInt(1,n,"k");
	inf.readSpace();
	int q = inf.readInt(0,std::min(n,0),"q");
	inf.readEoln();
	FOR(i,1,m){
		int u = inf.readInt(1,n);inf.readSpace();
		int v = inf.readInt(1,n);inf.readEoln();
		ensuref(u != v,"self-loop");
		ensuref(!mp[u][v],"repeated edges");
		mp[u][v] = mp[v][u] = 1;
	}
	FOR(i,1,n){
		inf.readInt(1,1e9,"ai");
		inf.readSpace();
	}
	inf.readEoln();
	FOR(i,1,k){
		inf.readInt(1,1e9,"bi");
		inf.readSpace();
	}
	inf.readEoln();
	FOR(i,1,q){
		int c = inf.readInt(1,n,"ci");inf.readSpace();
		int d = inf.readInt(1,1e9,"di");inf.readEoln();
		ensuref(!vis[c],"ci == cj");
		vis[c] = 1;
	}
	dfs(1);
	ensuref(tot == n,"unconnected");
	inf.readEof();
	return 0;
}
