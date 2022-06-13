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
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count)

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
	int n, ii, cnt, sz;
	vector<int> xx, yy, es, ans, vis, cyc, tp, par;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n, ii = 0;
		xx.assign(n, 0);
		yy.assign(n, 0);
		es.assign(n, 0);
		ans.assign(n, 0);
		tp.assign(n, 0);
		vis.assign(n + 1, -1);
		cyc.assign(n + 1, 0);
		par.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
	}
	void check(int x) {
		vis[x] = 0, sz += 1;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(vis[to] == -1) check(to);
			cnt += !tp[i], tp[i] = 1;
		}
	}
	void dfs1(int x, int p) {
		vis[x] = 2, par[x] = p;
		for(auto i : mp[x]) if(i != p) {
			int to = es[i] ^ x;
			if(!vis[to]) dfs1(to, i);
			else if(vis[to] == 2) {
				int cur = x, rev = 0, best = INF;
				ii++;
				while(cur != to) {
					if(par[cur] < best) {
						best = par[cur];
						if(xx[par[cur]] != cur) rev = 1;
						else rev = 0;
					}
					cyc[cur] = ii;
					cur = es[par[cur]] ^ cur;
				}
				if(i < best) {
					best = i;
					if(xx[i] != cur) rev = 1;
					else rev = 0;
				}
				cyc[cur] = ii;
				cur = x;
				while(cur != to) {
					ans[par[cur]] = (rev ^ (xx[par[cur]] != cur));
					cur = es[par[cur]] ^ cur;
				}
				ans[i] = (rev ^ (xx[i] != cur));
			}
		}
		vis[x] = 1;
	}
	void dfs2(int x, int par) {
		if(par != -1) ans[par] = (xx[par] != x);
		for(auto i : mp[x]) if(i != par) {
			int to = es[i] ^ x;
			if(cyc[to]) continue;
			dfs2(to, i);
		}
	}
	void solve() {
		rep(i, 1, n) if(vis[i] == -1) {
			sz = cnt = 0;
			check(i);
			if(sz != cnt) {
				cout << "Impossible\n";
				return;
			}
		}
		rep(i, 1, n) if(!vis[i]) dfs1(i, -1);
		rep(i, 1, n) if(cyc[i]) dfs2(i, -1);
		rep(i, 0, n - 1) cout << (ans[i] ? ">" : "<");
		cout << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 0, n - 1) {
			int a, b;
			cin >> a >> b;
			yy[i] = a, xx[i] = b;
			mp[a].push_back(i);
			mp[b].push_back(i);
			es[i] = a ^ b;
		}
		solve();
	}
	return 0;
}


