#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(a) a.begin(), a.end()

using namespace std;
#define pii pair<int, int>
#define x first
#define y second
struct DSU {
	int n;
	vector<int> par, rk, sz, top, vis;
	void init_(int _n) {
		n = _n;
		sz.assign(n + 1, 1);
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		top.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		iota(all(par), 0);
		iota(all(top), 0);
	}
	int pos(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = pos(par[x]);
	}
	bool same(int a, int b) {
		return pos(a) == pos(b);
	}
	void set_top(int x, int val) {
		top[pos(x)] = val;
	}
	int get_top(int x) { return top[pos(x)]; }
	int get_sz(int x) { return sz[pos(x)]; }
	int set_vis(int x, int cur) { 
		int ans = vis[pos(x)];
		vis[pos(x)] = cur;
		return ans;
	}
	void unite(int a, int b, int c) {
		int aa = pos(a);
		int bb = pos(b);
		if(aa == bb) return;
		if(rk[bb] > rk[aa]) swap(aa, bb);
		par[bb] = aa;
		rk[aa] += (rk[aa] == rk[bb]);
		sz[aa] += sz[bb];
		top[aa] = c;
	}
	void unite(int a, int b) {
		int aa = pos(a);
		int bb = pos(b);
		if(aa == bb) return;
		if(rk[bb] > rk[aa]) swap(aa, bb);
		par[bb] = aa;
		rk[aa] += (rk[aa] == rk[bb]);
		sz[aa] += sz[bb];
	}
};
namespace solver {
	int n, k, cnt = 0, ii, tot = 0;
	DSU dsu;
	queue<pii> q;
	vector<DSU> s, up;
	vector<vector<pii>> es;
	vector<vector<vector<int>>> mp;
	vector<vector<int>> par, dep;
	void init_(int _n, int _k) {
		n = _n, k = _k, ii = 0;
		cnt = 0, tot = 0;
		mp.assign(k + 1, vector<vector<int>>(n + 1, vector<int>()));
		par.assign(k + 1, vector<int>(n + 1, 0));
		dep.assign(k + 1, vector<int>(n + 1, 0));
		es.assign(k + 1, vector<pii>());
		s.resize(k + 1);
		up.resize(k + 1);
		rep(i, 1, k) {
			s[i].init_(n);
			up[i].init_(n);
			iota(all(par[i]), 0);
		}
		while(q.size()) q.pop();
	}
	void dfs(int c, int x, int p, int d) {
		par[c][x] = p, dep[c][x] = d;
		if(up[c].set_vis(x, ii) != ii) up[c].set_top(x, x);
		for(auto i : mp[c][x]) if(i != p) {
			dfs(c, i, x, d + 1);
		}
	}
	void add_edge(int x, int y) {
		cnt ++;
		if(dsu.same(x, y)) return;
		dsu.unite(x, y);
		q.push({x, y});
	}
	void merge(int c, int x, int y, int yes) {
		if(s[c].get_sz(x) < s[c].get_sz(y)) swap(x, y);
		ii++;
		if(yes) {
			up[c].unite(x, y, up[c].get_top(x));
			up[c].set_vis(x, ii);
		}
		s[c].unite(x, y);
		mp[c][x].push_back(y);
		mp[c][y].push_back(x);
		dfs(c, y, x, dep[c][x] + 1);
	}
	void cycle(int c, int x, int y) {
		while(!up[c].same(x, y)) {
			x = up[c].get_top(x);
			y = up[c].get_top(y);
			if(dep[c][x] < dep[c][y]) swap(x, y);
			int to = par[c][x], val = up[c].get_top(to);
			up[c].unite(to, x, val);
			add_edge(to, x);
		}
	}
	void solve() {
		dsu.init_(n);
		int tot = 0;
		rep(i, 1, k) {
			tot += es[i].size();
			for(auto j : es[i]) {
				if(s[i].same(j.x, j.y)) {
					cycle(i, j.x, j.y);
					add_edge(j.x, j.y);
				}
				else merge(i, j.x, j.y, 0);
			}
		}
		while(q.size()) {
			pii cur = q.front(); q.pop();
			rep(i, 1, k) {
				if(s[i].same(cur.x, cur.y)) cycle(i, cur.x, cur.y);
				else merge(i, cur.x, cur.y, 1);
			}
		}
		if(tot == cnt) cout << "Yes\n";
		else cout << "No\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n, m, k;
		cin >> n >> m >> k;
		init_(n, k);
		rep(i, 1, m) {
			int a, b, c;
			cin >> a >> b >> c;
			es[c].push_back({a, b});
		}
		solve();
	}
	return 0;
}

