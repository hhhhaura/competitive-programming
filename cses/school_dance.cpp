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
	int n, m, ii;
	vector<int> match, vis;
	vector<vector<int>> mp;
	void init_(int _n, int _m) {
		n = _n, m = _m, ii = 0;
		match.assign(m + 1, -1);
		vis.assign(m + 1, 0);
		mp.assign(n + 1, vector<int>());
	}
	bool dfs(int x) {
		for(auto i : mp[x]) if(vis[i] != ii) {
			vis[i] = ii;
			if(match[i] == -1 || dfs(match[i])) {
				match[i] = x;
				return 1;
			}
		} 
		return 0;
	}
	void solve() {
		int ans = 0;
		rep(i, 1, n) ii++, ans += dfs(i);
		cout << ans << "\n";
		rep(i, 1, m) if(match[i] != -1)
			cout << match[i] << " " << i << "\n";
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	init_(n, m);
	rep(i, 1, k) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
	}
	solve();
	return 0;
}


