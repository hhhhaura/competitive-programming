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

namespace solver {
	int n, m;
	const int N = 100, M = 100;
	vector<vector<int>> mp, dp, pre;
	vector<vector<tuple<int, int, int, int>>> v;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		mp.assign(n + 1, vector<int>(m + 1, 0));
	}
	void build() {
		pre.assign(N + 1, vector<int>(M + 1, 0));
		dp.assign(N + 1, vector<int>(M + 1, 0));
		v.assign(2ll * N * M + 1, vector<tuple<int, int, int, int>>());
		rep(i, 1, N) rep(j, 1, M) {
			vector<int> cnt(i * j + 1, 0);
			pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1]
				^ pre[i - 1][j - 1];
			rep(a, 1, i) rep(b, 1, j) {
				int val = pre[i][j] ^ pre[a - 1][j]
					^ pre[i][b - 1] ^ pre[a - 1][b - 1];
				if(val <= i * j) cnt[val] ++;
			}
			rep(a, 0, i * j) if(!cnt[a]) {
				dp[i][j] = a;
				break;
			}
			rep(a, 1, i) rep(b, 1, j) {
				int val = pre[i][j] ^ pre[a - 1][j]
					^ pre[i][b - 1] ^ pre[a - 1][b - 1];
				int to = val ^ dp[i][j];
				v[to].push_back({i, j, a, b});
			}
			pre[i][j] ^= dp[i][j];
		}
	}
	void solve() {
		int ans = 0;
		rep(i, 1, n) rep(j, 1, m) {
			if(mp[i][j]) ans ^= dp[i][j];
		}
		if(!ans) cout << "No\n";
		else {
			tuple<int, int, int, int> best = {INF, INF, INF, INF};
			int cnt = 0;
			for(auto i : v[ans]) {
				int a, b, c, d;
				tie(a, b, c, d) = i;
				if(a > n || b > m) continue;
				if(!mp[a][b]) continue;
				cnt ++;
				best = min(best, {n-a+1, m-b+1, n-c+1, m-d+1});
			}
			int a, b, c, d;
			tie(a, b, c, d) = best;
			cout << cnt << " " << a << " ";
			cout << b << " " << c << " " << d << "\n"; 
		}
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; build();
	while(cin >> n >> m) {
		init_(n, m);
		rep(i, 1, n) rep(j, 1, m) {
			int x; cin >> x;
			mp[n - i + 1][m - j + 1] = x;
		}
		solve();
	}
	return 0;
}



