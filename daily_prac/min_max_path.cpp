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
	int n;
	const int P = 500 + 1;
	vector<int> a;
	int dp[P][P][P];
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) {
			dp[i][j][k] = INF;

		}
	}
	void solve() {
		rep(i, a[i], n) dp[1][a[1]][i] = 0;
		rep(i, 1, n - 1) rep(j, 0, n)  {
			rep(k, 0, n) {
				int to = i + j + k;
				if(dp[i][j][k] == INF || to > n) continue;
				int mn = min(a[to], j);
				if(a[to] < k) {
					dp[to][mn][k] = min(dp[i][j][k] + 1, dp[to][mn][k]);
				}
				else if(a[to] == k) rep(m, 0, k) dp[to][mn][m] 
					= min(dp[i][j][k] + 1, dp[to][mn][m]);
			}
		}
		int ans = INF;
		rep(i, 0, n) ans = min(ans, dp[n][i][a[n]]);
		cout << (ans == INF ? -1 : ans)  << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> a[i];
		solve();
	}
	return 0;
}
