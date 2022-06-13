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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s; cin >> s;
	int n = s.size();
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
	vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
	rep(i, 0, n) C[i][0] = 1;
	rep(i, 1, n) rep(j, 1, n) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	rep(i, 0, n - 2) if(s[i] == s[i + 1]) dp[i][i + 1] = 1;
	rep(i, 1, n - 1) dp[i][i - 1] = 1;
	for(int len = 3; len < n; len += 2) {
		rep(i, 0, n - 1 - len) {
			int j = i + len;
			rep(k, i + 1, j - 1) if(s[k] == s[i]) 
				dp[i][j] += dp[i + 1][k - 1] * dp[k + 1][j] % MOD
					* C[(len + 1) / 2][(j - k) / 2] % MOD;
			if(s[i] == s[j]) dp[i][j] += dp[i + 1][j - 1];
			dp[i][j] %= MOD;
		}
	}
	cout << dp[0][n - 1] << "\n";
	return 0;
}


