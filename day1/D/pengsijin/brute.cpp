#include<bits/stdc++.h>
using namespace std;

const int _ = 3e7 + 7; int N , Q , fac[_] , ifac[_] , val[_] , P;
int poww(long long a , int b){int tms = 1; while(b){if(b & 1) tms = tms * a % P; a = a * a % P; b >>= 1;} return tms;}

int main(){
	cin >> Q >> P;
	fac[0] = 1; for(int i = 1 ; i < _ ; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	val[0] = 1; for(int i = 3 ; i < _ ; i += 3) val[i] = val[i - 3] * ((i - 1ll) * (i - 2) / 2 % P) % P;
	ifac[_ - 1] = poww(fac[_ - 1] , P - 2); for(int i = _ - 2 ; ~i ; --i) ifac[i] = ifac[i + 1] * (i + 1ll) % P;
	while(Q--){
		cin >> N; int ans = 0;
		if(N % 3 == 0) ans = val[N];
		else for(long long i = 0 ; i <= N ; i += 3) ans = (ans + 1ll * fac[N] * ifac[i] % P * ifac[N - i] % P * val[i] % P * (N - i - (N - i == 2))) % P;
		cout << ans << endl;
	}
	return 0;
}
