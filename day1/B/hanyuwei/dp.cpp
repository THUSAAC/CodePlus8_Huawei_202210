//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define inf 20021225
#define N (1<<18)
#define M 7000
#define lowbit(x) (x&-x)
using namespace std;
int read()
{
    int s=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')    f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')    s=s*10+ch-'0',ch=getchar();
    return s*f;
}
int n,m,q,k,a[20],b[20],d[20],f[7000000],g[7000000],e[20],pw[20],es[1000000],id[1000000];
int decode(int s,int x){return d[x]?s/pw[x]%3:s/pw[x]%2;}
int encode(int s,int x,int v){return s+pw[x]*v;}
void upd(int x,int fx,int gx){if(fx<f[x])	f[x]=fx,g[x]=gx; else if(fx==f[x]&&gx<g[x])	g[x]=gx;}
int main()
{
	n=read(),m=read(),k=read(),q=read(); int u,v; pw[0]=1;
	memset(f,63,sizeof(f)); memset(g,63,sizeof(g));
	for(int i=0;i<m;i++)	u=read()-1,v=read()-1,e[u]|=1<<v,e[v]|=1<<u;
	for(int i=0;i<n;i++)	id[1<<i]=i;
	for(int s=0;s<(1<<n);s++)
		for(int i=0;i<n;i++)	if(s>>i&1)
			es[s]|=e[i];
	for(int i=0;i<n;i++)	a[i]=read();
	for(int i=0;i<k;i++)	b[i]=read();
	for(int i=0;i<q;i++)	u=read()-1,d[u]=read();
	for(int i=1;i<=n;i++)
		if(d[i-1])	pw[i]=3*pw[i-1];
		else	pw[i]=2*pw[i-1];
	for(int i=0;i<n;i++)
	{
		int s=pw[i],fx=0;
		while(fx<k && a[i]>b[fx])	fx++; 
		upd(s,fx,a[i]);
	}
	for(int s=0;s<pw[n];s++)	if(f[s]<f[pw[n]])
	{
		int curs=0,v,ds=0; //printf("!%d %d %d\n",s,f[s],g[s]);
		for(int i=0;i<n;i++)	if(v=decode(s,i))
		{
			curs|=1<<i;
			if(d[i] && v==1)	ds|=1<<i;
		}
		if(curs==(1<<n)-1)	upd(pw[n]-1,f[s],g[s]);
		for(int i=0;i<n;i++)	if((!decode(s,i))&&(es[curs]>>i&1))
		{
			if(g[s]+a[i]<=b[f[s]])	upd(encode(s,i,1),f[s],g[s]+a[i]);
			else
			{
				int fx=f[s]+1;
				while(fx<k && a[i]>b[fx])	fx++; 
				upd(encode(s,i,1),fx,a[i]);
			}
			int ns=encode(s,i,1);
			for(int j=ds;j;j^=lowbit(j))
			{
				int di=id[lowbit(j)];
				if(g[s]+max(a[i]-d[di],0)<=b[f[s]])
					upd(encode(ns,di,1),f[s],g[s]+max(a[i]-d[di],0));
				else
				{
					int fx=f[s]+1;
					while(fx<k && max(a[i]-d[di],0)>b[fx])	fx++; 
					upd(encode(ns,di,1),fx,max(a[i]-d[di],0));
				}
			}
		}
	}
	if(f[pw[n]-1]<k)	printf("%d %d\n",f[pw[n]-1]+1,b[f[pw[n]-1]]-g[pw[n]-1]);
	else	printf("FAIL");
	return 0;
}
