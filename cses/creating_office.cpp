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

#define INF 1000000000
#define MOD 1000000007
#define eps (1e-9)
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
#define x first
#define y second
namespace solver {
	int n, d, lg;
	vector<vector<int>> mp, dis;
	vector<int> dep, sz, mx, mn, pos, up, ch;
	void init_(int _n, int _d) {
		n = _n, d = _d;
		lg = 31 - __builtin_clz(n);
		mp.assign(n + 1, vector<int>());
		dis.assign(lg + 1, vector<int>(n + 1, 0));
		dep.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		mn.assign(n + 1, INF);
		pos.assign(n + 1, 0);
		up.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		ch.push_back(x);
		for(auto i : mp[x]) if(i != par) {
			get_sz(i, x);
			sz[x] += sz[i];
			mx[x] = max(mx[x], sz[i]);
		}
	}
	void dfs1(int x, int par, int d) {
		dep[x] = d;
		for(auto i : mp[x]) if(i != par) {
			dfs1(i, x, d + 1);
		}
	}
	void dfs2(int x, int par, int id, int d) {
		dis[id][x] = d;
		for(auto i : mp[x]) if(i != par) {
			dfs2(i, x, id, d + 1);
		}
	}
	void deco(int x, int id, int par) {
		ch.clear();
		get_sz(x, x);
		int cen = x;
		for(auto i : ch) {
			if(max(sz[x] - sz[cen], mx[cen]) > 
				max(sz[x] - sz[i], mx[i])) cen = i;
		}
		pos[cen] = id;
		up[cen] = par;
		dfs2(cen, cen, id, 0);
		for(auto i : mp[cen]) {
			vector<int> tp;
			for(auto j : mp[i]) if(j != cen)
				tp.push_back(j);
			mp[i] = tp;
			deco(i, id + 1, cen);
		}
	}
	int query(int x) {
		int id = pos[x], cur = x, ans = mn[x];
		while(id) {
			int to = up[cur];
			ans = min(ans, mn[to] + dis[id - 1][x]);
			id --, cur = to;	
		}
		return ans;
	}
	void modify(int x) {
		int id = pos[x], cur = x;
		mn[x] = 0;
		while(id) {
			int to = up[cur];
			mn[to] = min(mn[to], dis[id - 1][x]);
			id--, cur = to;
		}
	}
	void solve() {
		dfs1(1, 1, 0);
		vector<int> ord(n, 0);
		iota(all(ord), 1);
		sort(all(ord), [&](int a, int b) {
			return dep[a] > dep[b];
		});
		deco(1, 0, 1);
		int cnt = 0;
		vector<int> ans;
		print("here");
		for(auto i : ord) {
			if(query(i) >= d) {
				cnt ++;
				modify(i);
				ans.push_back(i);
			}
		}
		cout << cnt << "\n";
		rep(i, 0, cnt - 1) cout << ans[i] << " \n"[i + 1 == cnt];
	}
};

using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, d;
	cin >> n >> d;
	init_(n, d);
	rep(i ,1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	solve();
	return 0;
}


