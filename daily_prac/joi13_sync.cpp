#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()

using namespace std;

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr << "Line " << __LINE__, kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m, q, timestamp;
	vector<vector<int>> mp;
	vector<int> ans, top, par, mx, id, sz;
	vector<int> v, es, x, y, vis, pos, pre;
	void init_(int _n, int _m, int _q) {
		n = _n, m = _m, q = _q;
		timestamp = 0;
		vis.assign(n, 1), pre.assign(n, 0);
		x.assign(n, 0), y.assign(n, 0);
		es.assign(n, 0);
		mp.assign(n + 1, vector<int>());
		ans.assign(n + 1, 1);
		top.assign(n + 1, 0);
		par.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		pos.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		id.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		v.assign(2 * n + 1, 0);
	}
	void get_info(int x, int p) {
		sz[x] = 1;
		for(auto i : mp[x]) if(i != p) {
			int to = es[i] ^ x;
			get_info(to, i);
			sz[x] += sz[to], par[to] = x;
			if(sz[to] > sz[mx[x]]) mx[x] = to;
		}
	}
	void hld(int x, int p, int tp) {
		top[x] = tp;
		id[x] = ++timestamp;
		pos[timestamp] = x;
		if(mx[x]) hld(mx[x], x, tp);
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == mx[x] || to == p) continue;
			hld(to, x, to);
		}
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		v[nd] = max(v[get(L, mid)], v[get(mid + 1, R)]);
	}
	void modify(int L, int R, int id, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = val;
		else {
			if(id <= mid) modify(L, mid, id, val);
			else modify(mid + 1, R, id, val);
			pull(L, R);
		}
	}
	int query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		else if(l <= L && r >= R) return v[nd];
		else return max(query(L, mid, l, r), query(mid + 1, R, l, r));
	}
	void change(int num) {
		modify(1, n, id[x[num]], (vis[num] ? id[x[num]] : 0));
		vis[num] ^= 1;
	}
	int get_id(int x) {
		int cur = x;
		while(cur) {
			int pa = top[cur];
			int val = query(1, n, id[pa], id[cur]);
			if(!val) cur = par[pa];
			else return pos[val];
		}
		assert(0);
	}
	void solve() {
		get_info(1, -1);
		hld(1, 1, 1);
		modify(1, n, id[1], id[1]);
		rep(i, 1, n - 1) if(id[x[i]] < id[y[i]]) swap(x[i], y[i]);
		rep(i, 1, n - 1) change(i); 
		rep(i, 1, m) {
			int cur; cin >> cur;
			if(!vis[cur]) {
				int a = get_id(x[cur]);
				int b = get_id(y[cur]);
				pre[cur] = ans[a] + ans[b] - pre[cur];
				ans[b] = pre[cur];
				change(cur);
			}
			else {
				change(cur);
				int a = get_id(x[cur]);
				int b = get_id(y[cur]);
				pre[cur] = ans[b];
				ans[a] = ans[b];
			}
		}
		rep(i, 1, q) {
			int cur; cin >> cur;
			cout << ans[get_id(cur)] << "\n";
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	init_(n, m, q);
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		x[i] = a, y[i] = b;
		es[i] = a ^ b;
		mp[a].push_back(i);
		mp[b].push_back(i);
	}
	solve();
	return 0;
}

