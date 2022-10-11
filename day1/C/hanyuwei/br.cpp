//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<stack>
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
struct sgt{int son[2],mx; ll f;}tr[N<<2];
int calc(int x,int l,int r,int mx)
{
	if(!x)	return 0;
	if(l==r)	return tr[x].mx>mx;
	if(mx>tr[ls(x)].mx)	return calc(rs(x),mid+1,r,mx);
	else	return tr[x].f-tr[ls(x)].f+calc(ls(x),l,mid,mx);
}
void upd(int x,int l,int r)
{
	tr[x].mx=max(tr[ls(x)].mx,tr[rs(x)].mx);
	tr[x].f=tr[ls(x)].f+calc(rs(x),mid+1,r,tr[ls(x)].mx);
}
int merge(int x,int y,int l,int r)
{
	if(!x||!y)	return x|y;
	ls(x)=merge(ls(x),ls(y),l,mid);
	rs(x)=merge(rs(x),rs(y),mid+1,r);
	upd(x,l,r);
	return x;
}
int seg;
void build(int &x,int l,int r,int d)
{
	x=++seg,tr[x].f=1,tr[x].mx=a[d];
	if(l==r)	return void();
	if(d<=mid)	build(ls(x),l,mid,d); else	build(rs(x),mid+1,r,d);
}
struct edge{int to,lt;}e[N<<1]; int in[N<<1],cnt;
void add(int x,int y){e[++cnt].lt=in[x]; in[x]=cnt; e[cnt].to=y;}
ll ans[N];
bool vis[N];
int main()
{
	scanf("%s",ch+1); n=strlen(ch+1); 
	for(int i=1;i<=n;i++)	a[i]=read();
	for(int i=1;i<=n;i++)
	{
		memset(vis+1,0,n-i+1); int mx=0;
		for(int l=1;l+i-1<=n;l++)	if(!vis[l])
		{
			mx=a[l+i-1]; ans[i]++;
			for(int j=l+1;j<=n;j++)
			{
				int wei=0;
				for(int k=0;k<i;k++)	if(ch[j+k]!=ch[l+k]){wei=1;break;}
				if(!wei)
				{
					vis[j]=1;
					if(a[j+i-1]>mx)	mx=a[j+i-1],ans[i]++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)	printf("%lld%c",ans[i]," \n"[i==n]);
	return 0;
}

