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
	string s; cin >> s;
	int k; cin >> k;
	int n = s.size();
	const int w = 37;
	vector<int> pre(n + 1, 0), inv(n + 1, 0);
	vector<int> v, dp(n + 1, 0), len;
	int cur = 1;
	auto pow_ = [](int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	rep(i, 1, n) {
		pre[i] = pre[i - 1] + cur * (s[i - 1] - 'a' + 1) % MOD;
		pre[i] = pre[i] % MOD;
		inv[i] = pow_(cur, MOD - 2);
		cur = cur * w % MOD;
	}
	rep(i, 0, k - 1) {
		string s; cin >> s;
		int cur = 1, ans = 0;
		for(auto j : s) {
			ans = (ans + (j - 'a' + 1) * cur % MOD) % MOD;
			cur = cur * w % MOD;
		}
		v.push_back(ans);
		len.push_back(s.size());
	}
	dp[0] = 1;
	rep(i, 1, n) rep(j, 0, k - 1) {
		if(len[j] <= i) {
			int to = (pre[i] - pre[i - len[j]]) ;
			to = (to < 0 ? to + MOD : to);
			to = (to * inv[i - len[j] + 1]) % MOD;
			if(to == v[j]) dp[i] = (dp[i] + dp[i - len[j]]);
			if(dp[i] > MOD) dp[i] -= MOD;
		}
	}
	cout << dp[n] << "\n";
	return 0;
}


