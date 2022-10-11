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
int n,m,k,q,vis[20][20],d[20];
int main(){
	int tot = 20;
	for(int tsd = 1;tsd <= tot;++tsd){
		char ch[50];
		sprintf(ch,"%d.in",tsd);
		freopen(ch,"r",stdin);
		n = read(1,18);
		m = read(1,n*(n-1)/2);
		k = read(1,n);
		q = read(0,min(n,8));
		for(int i=0;i<m;i++)
		{
			int u=read(1,n)-1,v=read(1,n)-1;
			assert(u>=0 && u<n);
			assert(v>=0 && v<n);
			assert(!vis[u][v] && !vis[v][u]);
			vis[u][v]=vis[v][u]=1;
		}
		for(int i=0;i<n;i++)	read(1,1000000000);
		for(int i=0;i<k;i++)	read(1,1000000000);
		for(int i=0;i<q;i++)	u=read(1,n)-1,assert(!d[u]),d[u]=read(1,1000000000);
		end_chk();
		fclose(stdin); 
	} 
	return 0;
}
