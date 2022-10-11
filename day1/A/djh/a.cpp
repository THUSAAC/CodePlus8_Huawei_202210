#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> v;
string ans;

void solution1() {

  sort(v.begin(), v.end());
  reverse(v.begin(), v.end());

  long long B = 0, Y = 0, Z = 0;

  for(int i = 0; i < v.size(); ++i) {
    if(B <= Y) {
      if(B <= Z) {
        B += v[i];
        ans[i] = 'B';
      } else {
        Z += v[i];
        ans[i] = 'Z';
      }
    } else {
      if(Y <= Z) {
        Y += v[i];
        ans[i] = 'Y';
      } else {
        Z += v[i];
        ans[i] = 'Z';
      }
    }
  }

//  cout << B << " " << Y << " " << Z << endl;

  if(B + Y > Z && B + Z > Y & Y + Z > B) {
    cout << ans;
    exit(0);
  }


}

int main() {  
  scanf("%d", &n);
  v.resize(n);
  ans.resize(n);
  for(int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }

  solution1();

  // printf("Internationale!");
  puts("Internationale!")
  return 0;

}