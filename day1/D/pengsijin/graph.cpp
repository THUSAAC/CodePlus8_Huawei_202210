#include<bits/stdc++.h>
using namespace std;

const int _ = 3e7 + 7; int inv[_] , fac[_] , val[_] , val3[_] , N , Q , P;

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> Q >> P; val3[0] = val[0] = fac[0] = inv[1] = 1;
	for(int i = 1 ; i < _ ; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	for(int i = 3 ; i < _ ; i += 3) val3[i] = val3[i - 3] * ((i - 1ll) * (i - 2) / 2 % P) % P;
	for(int i = 2 ; i < _ ; ++i) inv[i] = P - 1ll * inv[P % i] * (P / i) % P;
	for(int i = 1 ; i < _ ; ++i) val[i] = (val[i - 1] + (i >= 3 ? val[i - 3] * (P + 1ll) / 2 : 0ll)) % P * inv[i] % P;
	while(Q--){
		cin >> N; int ans;
		if(N % 3 == 0) ans = val3[N];
		else ans = (1ll * val[N - 1] * fac[N] + (N % 3 == 2 ? P - N * (N - 1ll) / 2 % P * val3[N - 2] % P : 0)) % P;
		cout << ans << endl;
	}
	return 0;
}
