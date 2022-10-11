#include<bits/stdc++.h>
using namespace std;

int main(){
	int N  , Q = 1e5; mt19937 rnd(time(0));
	cin >> N;
	cout << min(N , Q) << '\n';
	if(Q <= N){
		for(int i = 1 ; i <= Q / 10 ; ++i) cout << i << '\n';
		for(int i = 1 ; i <= Q / 10 ; ++i) cout << N + 1 - i << '\n';
		for(int i = 1 ; i <= Q - Q / 10 * 2 ; ++i) cout << rnd() % N + 1 << '\n';
	}else{for(int i = 1 ; i <= N ; ++i) cout << i << '\n';}
	return 0;
}
