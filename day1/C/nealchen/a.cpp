#include <bits/stdc++.h>
int main() {
	std::string s;
	std::cin >> s;
	size_t n = s.size();
	std::vector<int> a(n);
	for (size_t i = 0; i != n; ++i) {
		std::cin >> a[i];
	}
	std::stack<int> stack;
	std::vector<int> ans(n + 1);
	for (size_t i = n; i != 0; --i) {
		int val = a[i - 1];
		while (!stack.empty() && val >= stack.top()) {
			stack.pop();
		}
		stack.push(val);
		ans[i] = stack.size();
	}
	for (int i = 1; i <= n; ++i) {
		std::cout << ans[i] << " \n"[i == n];
	}
	return 0;
}