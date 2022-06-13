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
	int n, lg;
	vector<vector<int>> mp, ac;
	vector<int> dp, dep;
	void init_(int _n) {
		n = _n;
		lg = 31 - __builtin_clz(n);
		dep.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
		ac.assign(lg + 1, vector<int>(n + 1, 0));
	}
	void dfs(int x, int p, int d) {
		ac[0][x] = p, dep[x] = d;
		for(auto i : mp[x]) if(i != p) {
			dfs(i, x, d + 1);
		}
	}
	int LCA(int a, int b) {
		if(dep[a] < dep[b]) swap(a, b);
		int need = dep[a] - dep[b];
		rep(i, 0, lg) if((need >> i) & 1)
			a = ac[i][a];
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a], b = ac[i][b];
		}
		return ac[0][a];
	}
	void build() {
		dfs(1, 0, 0);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	build();
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		int lca = LCA(a, b);
		dp[a] ++, dp[b] ++;
		dp[lca] --, dp[ac[0][lca]]--;
	}
	vector<int> a;
	rep(i, 1, n) a.push_back(i);
	sort(all(a), [&](int x, int y) {
		return dep[x] > dep[y];
	});
	for(auto i : a) {
		int par = ac[0][i];
		dp[par] += dp[i];
	}
	rep(i, 1, n) cout << dp[i] << " \n"[i == n];
	return 0;
}


