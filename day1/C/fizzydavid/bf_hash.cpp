//by yjz
#include<bits/stdc++.h>
#define FF first
#define SS second
#define MP make_pair
#define PB push_back
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int maxn = 100011;
char s[maxn];
int a[maxn];
int n;
ull seed[maxn];
int ans[maxn];
unordered_map<ull, int> m;
int main()
{
	scanf("%s", s+1);
	n = strlen(s+1);
	for (int i=1; i<=n; i++) scanf("%d", &a[i]);
	for (int i=0; i<=n; i++) {
		seed[i] = rand();
		seed[i] = seed[i]*RAND_MAX + rand();
		seed[i] = seed[i]*RAND_MAX + rand();
		seed[i] = seed[i]*RAND_MAX + rand();
	}
	for (int i=1; i<=n; i++) {
		ull hs = 0;
		for (int j=0; j<=n-i; j++) {
			hs += seed[j] * s[i+j];
			int &mx = m[hs];
			ans[j+1] += mx < a[i+j];
			mx = max(mx, a[i+j]);
		}
	}
	for (int i=1; i<=n; i++) printf("%d%c", ans[i], i==n?'\n':' ');
	return 0;
}