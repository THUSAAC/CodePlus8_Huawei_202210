#include <bits/stdc++.h>
int main() {
	std::string s;
	std::cin >> s;
	size_t n = s.size();
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	std::map<std::string, std::vector<int>> pos;
	for (int i = 0; i != n; ++i) {
		for (int l = 1; l <= n - i; ++l) {
			pos[s.substr(i, l)].push_back(a[i + l]);
		}
	}
	std::vector<int> ans(n + 1);
	for (auto pair : pos) {
		int len = pair.first.size();
		int prefix_max = 0;
		for (int a : pair.second) {
			if (a > prefix_max) {
				prefix_max = a;
				++ans[len];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		std::cout << ans[i] << " \n"[i == n];
	}
	return 0;
}