//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define inf 20021225
#define N 100100
#define ls(x) tr[x].son[0]
#define rs(x) tr[x].son[1]
#define mid (l+r>>1)
using namespace std;
int read()
{
    int s=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')    f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')    s=s*10+ch-'0',ch=getchar();
    return s*f;
}
struct node{int fa,len,ch[26],ed;}t[N*20]; int rt,poi,lt;
int a[N],n; char ch[N];
void insert(int c,int id)
{
	int p=lt,np=lt=++poi; t[np].ed=id; t[np].len=t[p].len+1;
    for(;p&&!t[p].ch[c];p=t[p].fa)    t[p].ch[c]=np;
    if(!p){t[np].fa=rt; return;}
    int q=t[p].ch[c];
    if(t[q].len==t[p].len+1){t[np].fa=q; return;}
    int nq=++poi; t[nq].fa=t[q].fa; t[q].fa=t[np].fa=nq;
    memcpy(t[nq].ch,t[q].ch,sizeof(t[q].ch)); t[nq].len=t[p].len+1;
    for(;p&&t[p].ch[c]==q;p=t[p].fa)    t[p].ch[c]=nq;
}
struct sgt{int son[2],mx,mn; ll f;}tr[N*20]; int qwq;
void upd(int x)
{
	if(!x)	return;
	tr[x].f=tr[ls(x)].f+tr[rs(x)].f;
	tr[x].mx=max(tr[ls(x)].mx,tr[rs(x)].mx);
	tr[x].mn=min(tr[ls(x)].mn,tr[rs(x)].mn);
}
int upd(int x,int mx)
{
	if(!x)	return 0;
	if(tr[x].mx<=mx)	return 0;
	if(tr[x].mn>mx)	return x;
	ls(x)=upd(ls(x),mx);
	rs(x)=upd(rs(x),mx);
	upd(x);
	//printf("%d %d %d\n",x,ls(x),rs(x));
	return x;
}
int merge(int x,int y,int l,int r)
{
	if(!x||!y)	return x|y;// qwq++; if(qwq>10000)printf("%d %d %d %d\n",x,y,l,r);
	ls(x)=merge(ls(x),ls(y),l,mid);
	rs(x)=merge(rs(x),rs(y),mid+1,r);
	if(ls(x))	rs(x)=upd(rs(x),tr[ls(x)].mx);
	upd(x);
	return x;
}
int seg;
void build(int &x,int l,int r,int d)
{
	x=++seg,tr[x].f=1,tr[x].mx=tr[x].mn=a[d];
	if(l==r)	return void();
	if(d<=mid)	build(ls(x),l,mid,d); else	build(rs(x),mid+1,r,d);
}
struct edge{int to,lt;}e[N<<1]; int in[N<<1],cnt;
void add(int x,int y){e[++cnt].lt=in[x]; in[x]=cnt; e[cnt].to=y;}
ll ans[N];
int dfs(int x)
{
	int crt=0;
	if(t[x].ed)	build(crt,1,n,t[x].ed);
	for(int i=in[x];i;i=e[i].lt)	crt=merge(crt,dfs(e[i].to),1,n);
	ans[t[t[x].fa].len+1]+=tr[crt].f;
	ans[t[x].len+1]-=tr[crt].f;
	return crt;
}
int main()
{
	scanf("%s",ch+1); n=strlen(ch+1); rt=lt=poi=1; tr[0].mn=1000000001;
	for(int i=1;i<=n;i++)	a[i]=read();
	for(int i=1;i<=n;i++)	insert(ch[i]-'a',i);
	for(int i=2;i<=poi;i++)	add(t[i].fa,i);
	dfs(rt);
	for(int i=1;i<=n;i++)	ans[i]+=ans[i-1];
	for(int i=1;i<=n;i++)	printf("%lld%c",ans[i]," \n"[i==n]);
	return 0;
}

