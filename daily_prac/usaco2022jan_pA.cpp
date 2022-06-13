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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	const int P = 1000;
	vector<int> a(n + 1, 0);
	vector<vector<int>> pre(n + 1, vector<int>(P + 1, 0));
	vector<vector<int>> dp(n + 1, vector<int>(P + 1, 0));
	auto solve = [&](int x) {
		rep(i, 0, n) rep(j, 0, P) {
			dp[i][j] = 0;
			pre[i][j] = 0;
		}
		dp[0][0] = 1;
		rep(i, 0, P) pre[0][i] = 1;
		rep(i, 1, n) {
			rep(j, 0, a[i] - x) dp[i][j] = pre[i - 1][a[i] - x - j];
			pre[i][0] = dp[i][0];
			rep(j, 1, P) pre[i][j] = (dp[i][j] + pre[i][j - 1]) % MOD;
		}
		return dp[n][0];
	};
	int mn = INF, ans = 0;
	rep(i, 1, n) cin >> a[i], mn = min(mn, a[i]);
	if(n & 1) {
		rep(i, 0, mn) ans = (ans + solve(i)) % MOD;
		cout << ans << "\n";
	}
	else cout << solve(0) << "\n";
	return 0;
}



