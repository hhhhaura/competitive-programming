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
	int n, m, ans;
	set<int> v[2], h[2];
	vector<int> row, col;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		v[0].clear();
		v[1].clear();
		h[0].clear();
		h[1].clear();
		row.assign(n + 1, 0);
		col.assign(n + 1, 0);
	}
	void modify1(int x) {
		int cur = row[x];
		h[cur].erase(h[cur].find(x));
		cur ^= 1;
		h[cur].insert(x);
		row[x] = cur;
	}
	void modify2(int x) {
		int cur = col[x];
		v[cur].erase(v[cur].find(x));
		cur ^= 1;
		v[cur].insert(x);
		col[x] = cur;
	}
	void dfs(int x, int y, int tx, int ty, int dir, int to, int times) {
		if(times >= 5 || ans) return;
		if(dir == 0) {
			if(tx <= x && (y == ty || (row[tx] ^ (ty < y)))) {
				ans = 1;
				return;
			}
			auto L = h[to].begin(), R = h[to].upper_bound(x);
			if(R != L) dfs(*prev(R), y, tx, ty, 2 + to, 0, times + 1);
			if(h[to].size() && *L <= x) dfs(*L, y, tx, ty, 2 + to, 1, times + 1);
		}
		else if(dir == 1) {
			if(tx >= x && (y == ty || (row[tx] ^ (ty < y)))) {
				ans = 1;
				return;
			}
			auto L = h[to].lower_bound(x), R = h[to].end();
			if(R != h[to].begin() && *prev(R) >= x) 
				dfs(*prev(R), y, tx, ty, 2 + to, 0, times + 1);
			if(L != h[to].end()) dfs(*L, y, tx, ty, 2 + to, 1, times + 1);
		}
		else if(dir == 2) {
			if(ty <= y && (x == tx || (col[ty] ^ (tx < x)))) {
				ans = 1;
				return;
			}
			auto L = v[to].begin(), R = v[to].upper_bound(y);
			if(R != L) dfs(x, *prev(R), tx, ty, to, 0, times + 1);
			if(v[to].size() && *L <= y) dfs(x, *L, tx, ty, to, 1, times + 1);
		}
		else {
			if(ty >= y && (x == tx || (col[ty] ^ (tx < x)))) {
				ans = 1;
				return;
			}
			auto L = v[to].lower_bound(y), R = v[to].end();
			if(R != v[to].begin() && *prev(R) >= y) 
				dfs(x, *prev(R), tx, ty, to, 0, times + 1);
			if(L != v[to].end()) dfs(x, *L, tx, ty, to, 1, times + 1);
		}
	}
	bool check(int x, int y, int x1, int y1) {
		ans = 0;
		dfs(x, y, x1, y1, col[y], 0, 0);
		dfs(x, y, x1, y1, col[y], 1, 0);
		dfs(x, y, x1, y1, row[x] + 2, 0, 0);
		dfs(x, y, x1, y1, row[x] + 2, 1, 0);
		return ans;
	}
	void solve() {
		rep(i, 1, n) {
			char c; cin >> c;
			row[i] = (c == 'R');
			h[row[i]].insert(i);
		}
		rep(i, 1, n) {
			char c; cin >> c;
			col[i] = (c == 'D');
			v[col[i]].insert(i);
		}
		while(m--) {
			int tp; cin >> tp;
			if(tp == 1) {
				int x, y, x1, y1;
				cin >> x >> y >> x1 >> y1;
				if(check(x, y, x1, y1)) cout << "YES\n";
				else cout << "NO\n";
			}
			else if(tp == 2) {
				int x; cin >> x;
				modify1(x);
			}
			else {
				int x; cin >> x;
				modify2(x);
			}
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		init_(n, m);
		solve();
	}
	return 0;
}


