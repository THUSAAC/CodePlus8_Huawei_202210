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
	std::map<int, int> s_path;
	SAM::State *cur = s_SAM.root;
	for (size_t i = 0; i != n; ++i)
	{
		cur = s_SAM.extend(s[i] - 'a', cur);
		s_path.emplace(cur->id, i);
	}

	size_t m = s_SAM.states.size();
	std::vector<std::set<int>> premax(m);
	for (auto pair : s_path)
	{
		premax[pair.first].insert(pair.second);
	}
	std::vector<std::vector<int>> children(m);
	for (size_t i = 0; i != m; ++i) {
		SAM::State *p = s_SAM.states[i]->parent;
		if (p != nullptr) {
			children[p->id].push_back(i);
		}
	}

	std::vector<int> a(n);
	for (size_t i = 0; i != n; ++i)
	{
		std::cin >> a[i];
	}

	std::function<void(std::set<int> &, int)> insert_premax = [&a](std::set<int>& premax, int item)
	{
		std::set<int>::iterator lb = premax.lower_bound(item);
		if (lb != premax.begin())
		{
			std::set<int>::iterator prev = lb;
			--prev;
			if (a[*prev] >= a[item]) {
				return;
			}
		}
		while (lb != premax.end() && a[item] >= a[*lb])
		{
			lb = premax.erase(lb);
		}
		premax.insert(lb, item);
	};

	std::function<void(std::set<int> &, std::set<int> &)> join_premax = [insert_premax](std::set<int> &s1, std::set<int> &s2)
	{
		if (s1.size() < s2.size())
		{
			s1.swap(s2);
		}
		for (int item : s2)
		{
			insert_premax(s1, item);
		}
		std::set<int>().swap(s2);
	};

	std::vector<int> premax_size(m);
	std::function<void(int)> dfs = [&dfs, &children, &premax, &premax_size, join_premax](int u)
	{
		for (int v : children[u])
		{
			dfs(v);
			join_premax(premax[u], premax[v]);
		}
		premax_size[u] = premax[u].size();
	};
	dfs(s_SAM.root->id);
	
	std::vector<int> ans(n + 1);
	for (size_t i = 1; i != m; ++i)
	{
		ans[s_SAM.states[i]->parent->max_len] += premax_size[i];
		ans[s_SAM.states[i]->max_len] -= premax_size[i];
	}
	for (size_t i = 1; i != ans.size(); ++i)
	{
		ans[i] += ans[i - 1];
	}
	for (size_t i = 0; i != n; ++i)
	{
		std::cout << ans[i] << " \n"[i == n - 1];
	}
}