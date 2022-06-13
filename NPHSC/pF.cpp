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
	int n, k, yes;
	vector<vector<int>> mp;
	vector<int> a, dep, dp, ans;
	void init_(int _n, int _k) {
		n = _n, k = _k, yes = 1;
		mp.assign(n + 1, vector<int>());
		a.assign(n + 1, 0);
		dep.assign(n + 1, INF);
		dp.assign(n + 1, 0);
		ans.clear();
	}
	void dfs(int x, int par, int d) {
		dep[x] = d;
		if(!yes) return;
		if(mp[x].size() == 0) dp[x] = a[x];
		int cnt = 0;
		for(auto i : mp[x]) {
			dfs(i, x, d + 1);
			if(dep[dp[i]] > d) cnt ++, dp[x] = i;
			else if(!cnt && dep[dp[x]] > dep[dp[i]]) dp[x] = dp[i];
			if(cnt > 1) yes = 0;
			if(!yes) return;
		}
	}
	void get_ans(int x) {
		if(mp[x].size() == 0) ans.push_back(x);
		sort(all(mp[x]), [&](int a, int b) {
			return dep[dp[a]] > dep[dp[b]];
		});
		for(auto i : mp[x]) {
			if(dep[dp[i]] > dep[x]) continue;
			get_ans(i);
		}
		for(auto i : mp[x]) {
			if(dep[dp[i]] > dep[x]) get_ans(i);
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) {
		int t; cin >> t;
		rep(j, 1, t) {
			int s; cin >> s;
			mp[i].push_back(s);
		}
	}
	rep(i, 1, n) cin >> a[i];
	dfs(1, 1, 0);
	if(!yes) cout << "No\n", exit(0);
	cout << "Yes\n";
	get_ans(1);
	rep(i, 0, k - 1) cout << ans[i] << " \n"[i + 1 == k];
	return 0;
}

