#define wiwihorz
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	const int P = 10000000;
	vector<bool> cnt(P + 1, 0);
	vector<int> pre(P + 1, 0), dp(P + 1, 0);
	rep(i, 1, n) {
		int x; cin >> x;
		cnt[x] = 1;
	}
	rep(i, 1, P) for(int j = i; j <= P; j += i) pre[i] += cnt[j];
	rrep(i, 1, P) {
		dp[i] = pre[i] * (pre[i] - 1);
		for(int j = 2 * i; j <= P; j += i) dp[i] -= dp[j];
	}
	int ans = -n * (n - 1) * 2ll;
	rep(i, 1, P) {
		for(int j = i; j <= P; j += i) if(cnt[j]) ans += dp[i];
	}
	cout << ans << "\n";
	return 0;
}
