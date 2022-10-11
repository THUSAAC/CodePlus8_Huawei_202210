#include <bits/stdc++.h>

class SAM
{
public:
	struct State
	{
		int id, max_len;
		State *parent, *trans[26];
	};

	std::vector<State *> states;

	State *root;

	SAM()
	{
		root = new_node();
		root->max_len = 0;
		root->parent = nullptr;
		memset(root->trans, 0, sizeof(root->trans));
	}

	~SAM()
	{
		for (State *s : states)
		{
			delete s;
		}
	}

	State *extend(int c, State *cur)
	{
		State *next = cur->trans[c];
		if (next == nullptr)
		{
			next = new_node();
			memset(next->trans, 0, sizeof(next->trans));
			next->max_len = cur->max_len + 1;
			while (cur != nullptr && cur->trans[c] == nullptr) {
				cur->trans[c] = next;
				cur = cur->parent;
			}
			if (cur == nullptr) {
				next->parent = root;
			} else {
				next->parent = extend(c, cur);
			}
		} else if (next->max_len > cur->max_len + 1) {
			State *proto = next;
			next = new_node();
			memcpy(next->trans, proto->trans, sizeof(next->trans));
			next->parent = proto->parent;
			proto->parent = next;
			next->max_len = cur->max_len + 1;
			while (cur != nullptr && cur->trans[c] == proto) {
				cur->trans[c] = next;
				cur = cur->parent;
			}
		}
		return next;
	}

	void build(const std::string &s)
	{
		State *cur = root;
		for (char c : s)
		{
			cur = extend(c - 'a', cur);
		}
	}

private:
	State *new_node()
	{
		State *o = new State;
		o->id = states.size();
		states.push_back(o);
		return o;
	}
};

int main()
{
	std::string s;
	std::cin >> s;

	size_t n = s.size();

	SAM s_SAM;
	s_SAM.build(s);

	size_t m = s_SAM.states.size();

	std::vector<int> a(n);
	for (int i = 0; i != n; ++i)
	{
		std::cin >> a[i];
	}

	std::vector<int> ans(n);
	for (int len = 1; len <= n; ++len)
	{
		std::vector<int> max(m);
		int ans = 0;
		auto add_substring = [&max, &ans](int id, int val)
		{
			if (val > max[id])
			{
				max[id] = val;
				++ans;
			}
		};
		SAM::State *cur = s_SAM.root;
		for (size_t i = 0; i != len; ++i) {
			cur = cur->trans[s[i] - 'a'];
		}
		add_substring(cur->id, a[len - 1]);
		for (size_t r = len; r != n; ++r) {
			cur = cur->trans[s[r] - 'a'];
			if (len <= cur->parent->max_len) {
				cur = cur->parent;
			}
			add_substring(cur->id, a[r]);
		}
		std::cout << ans << " \n"[len == n];
	}
	return 0;
}