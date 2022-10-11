#include<bits/stdc++.h>
#define llong long long
#define mkpr make_pair
#define x first
#define y second
#define iter iterator
#define riter reverse_iterator
#define y1 Lorem_ipsum_
#define tm dolor_sit_amet_
#define pli pair<llong,int>
using namespace std;

inline int read()
{
	int x = 0,f = 1; char ch = getchar();
	for(;!isdigit(ch);ch=getchar()) {if(ch=='-') f = -1;}
	for(; isdigit(ch);ch=getchar()) {x = x*10+ch-48;}
	return x*f;
}

const int mxN = 2e5;
int n;
pli a[mxN+3]; llong sum;
char ans[mxN+3],str[3];

void assign(int x,int y)
{
	ans[a[x].y] = str[y];
}

void output()
{
	for(int i=1; i<=n; i++) printf("%c",ans[i]); puts("");
}

int main()
{
	n = read(); sum = 0ll; str[0] = 'B',str[1] = 'Y',str[2] = 'Z';
	for(int i=1; i<=n; i++) {a[i].x = read(),a[i].y = i; sum += a[i].x;}
	sort(a+1,a+n+1);
	if(a[n].x*2>=sum) {puts("Internationale!"); return 0;}
	if(a[n].x*4==sum&&a[n-1].x==a[n].x&&a[n-2].x==a[n].x)
	{
		if(n==4) {puts("Internationale!");}
		else
		{
			for(int i=n-2; i<=n; i++) {assign(i,n-i);}
			assign(1,0); for(int i=2; i<=n-3; i++) {assign(i,1);}
			output();
		}
		return 0;
	}
	int i = 1;
	for(int k=0; k<3; k++)
	{
		llong cur = 0ll;
		while(i<=n&&(cur+a[i].x)*2<sum) {cur += a[i].x; assign(i,k); i++;}
	}
	output();
	return 0;
}
