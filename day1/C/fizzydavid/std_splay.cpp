//by yjz
#include<bits/stdc++.h>
#define FF first
#define SS second
#define MP make_pair
#define PB push_back
typedef long long ll;
using namespace std;
const int maxn = 200111;
const int sigma = 27;
class splay_node {
public:
	splay_node* fa;
	splay_node* go[2];
	int key, val;
	splay_node(int k=0, int v=0) {
		key = k, val = v;
		fa = go[0] = go[1] = nullptr;
	}
};
class Splay {
public:
	splay_node *rt;
	int sz;
	vector<pair<int,int> > V;
	Splay() {
		rt = nullptr;
		sz = 0;
	}
	void init_tree(int x, int v) {
		rt = new splay_node(x, v);
		sz = 1;
	}
	bool getdir(splay_node *p) {
		return p->fa->go[0]==p ? 0 : 1;
	}
	void rotate(splay_node *p, bool d) {
		auto q = p->go[d];
		auto r = q->go[!d];
		if (p->fa) p->fa->go[getdir(p)] = q;
		p->go[d] = r;
		q->go[!d] = p;
		q->fa = p->fa;
		p->fa = q;
		if (r) r->fa = p;
	}
	void splay(splay_node *p, splay_node *target = nullptr) {
		while (p->fa != target) {
			auto q = p->fa;
			bool dq = getdir(p);
			if (q->fa == target) {
				rotate(q, dq);
			} else {
				auto r = q->fa;
				bool dr = getdir(q);
				if (dq==dr) {
					rotate(r, dr);
					rotate(q, dq);
				} else {
					rotate(q, dq);
					rotate(r, dr);
				}
			}
		}
	}
	splay_node* get_min(splay_node *p) {
		return p->go[0] ? get_min(p->go[0]) : p;
	}
	void insert_and_update(int key, int val) {
		auto p = rt, last_p = rt;
		while (p) {
			last_p = p;
			if (key < p->key) {
				p = p->go[0];
			} else {
				if (p->val >= val) return;
				p = p->go[1];
			}
		}
		sz++;
		p = last_p;
		splay(p);
		rt = new splay_node(key, val);
		p->fa = rt;
		bool dir = p->key > key;
		rt->go[dir] = p;
		auto q = p->go[!dir];
		p->go[!dir] = 0;
		if (q) {
			rt->go[!dir] = q;
			q->fa = rt;
		}
		//update
		auto last = rt;
		while (last->go[1]) {
			auto q = get_min(last->go[1]);
			splay(q, last);
			if (q->val <= val) {
				sz--;
				last = q;
			} else {
				break;
			}
		}
		rt->go[1] = last->go[1];
		if (last->go[1]) last->go[1]->fa = rt;
	}
	void merge(const vector<pair<int,int> > &v) {
		for (auto u : v) {
			insert_and_update(u.FF, u.SS);
		}
	}
	void extract_dfs(vector<pair<int,int> > &v, splay_node *p) {
		if (!p) return;
		extract_dfs(v, p->go[0]);
		v.PB(MP(p->key, p->val));
		extract_dfs(v, p->go[1]);
	}
	vector<pair<int,int> > extract() {
		vector<pair<int,int> > v;
		if (!sz) return v;
		extract_dfs(v, rt);
		return v;
	}
};
Splay* merge_splay(Splay* a, Splay* b) {
	if (a->sz > b->sz) swap(a, b);
	auto content = a->extract();
	b->merge(content);
	return b;
}
class SAM {
private:
	int go[maxn][sigma], pre[maxn], len[maxn], tot;
	vector<int> con[maxn];
	int pos[maxn];
public:
	SAM() {init();}
	void init() {
		memset(go, 0, sizeof(go));
		memset(pre, 0, sizeof(pre));
		memset(len, 0, sizeof(len));
		tot = 1;
	}
	int insert(int p, char c) {
		c -= 'a';
		int np = ++tot;
		len[np] = len[p] + 1;
		while (p && !go[p][c])
			go[p][c] = np, p = pre[p];
		if (!p) {
			pre[np] = 1;
		} else {
			int q = go[p][c];
			if (len[p] + 1 == len[q]) {
				pre[np] = q;
			} else {
				int nq = ++tot;
				len[nq] = len[p] + 1;
				memcpy(go[nq], go[q], sizeof(int) * sigma);
				pre[nq] = pre[q];
				pre[q] = pre[np] = nq;
				while (p && go[p][c] == q)
					go[p][c] = nq, p = pre[p];
			}
		}
		return np;
	}
	void set_pos(int p, int v) {
		pos[p] = v;
	}
	void build_tree() {
		for (int i=1; i<=tot; i++) {
			con[i].clear();
		}
		for (int i=1; i<=tot; i++) {
			if (pre[i]) con[pre[i]].PB(i);
		}
	}
	Splay* dfs(int ans[], int a[], int x) {
		Splay* cur = new Splay;
		if (pos[x]) {
			cur->init_tree(pos[x], a[pos[x]]);
		} else {
			for (auto u : con[x]) {
				cur = merge_splay(cur, dfs(ans, a, u));
			}
		}
		ans[len[x]] += cur->sz;
		ans[len[pre[x]]] -= cur->sz;
		// cerr<<"dfs:"<<x<<" "<<cur->sz<<" "<<len[x]<<","<<len[pre[x]]<<" : ";
		// auto tmp = cur->extract();
		// for (auto u : tmp) cerr<<u.FF<<","<<u.SS<<" "; cerr<<endl;
		return cur;
	}
	void solve(int n, int ans[], int a[]) {
		build_tree();
		for (int i=1; i<=n+1; i++) ans[i] = 0;
		dfs(ans, a, 1);
		for (int i=n; i>=1; i--) ans[i] += ans[i+1];
		for (int i=2; i<=n; i++) ans[i]--;
	}
}sam;

char s[maxn];
int n, a[maxn], ans[maxn];
int main()
{
	scanf("%s", s+1);
	n = strlen(s+1);
	for (int i=1; i<=n; i++) scanf("%d", &a[i]);
	int p = 1;
	sam.set_pos(p = sam.insert(p, 'z' + 1), 0);
	for (int i=1; i<=n; i++) {
		sam.set_pos(p = sam.insert(p, s[i]), i);
	}
	sam.solve(n, ans, a);
	for (int i=1; i<=n; i++) printf("%d%c", ans[i], i==n?'\n':' ');
	return 0;
}