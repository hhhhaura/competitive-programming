#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 998244353
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, l;
	cin >> n >> m >> l;
	assert(l <= 1000);
	vector<int> a(n + 1, 0), f(n + 1, 0);
	vector<vector<int>> dp(n + 1, vector<int>(l + 1, 0));
	vector<vector<int>> to(n + 1, vector<int>(m + 1, 0));
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) {
		int pre = f[i - 1];
		while(pre && a[pre + 1] != a[i]) pre = f[pre];
		if(a[pre + 1] == a[i]) pre ++;
		f[i] = pre;
	}
	rep(i, 0, n) rep(j, 1, m) {
		int cur = i;
		while(cur && a[cur + 1] != j) cur = f[cur];
		if(a[cur + 1] == j) cur ++;
		to[i][j] = cur;
	}
	dp[0][0] = 1;
	auto pow_ = [](int a, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	rep(j, 0, l - 1) rep(i, 0, n - 1) {
		rep(k, 1, m) {
			int nxt = to[i][k];
			dp[nxt][j + 1] += dp[i][j];
			dp[nxt][j + 1] %= MOD;
		}
	}
	int ans = 0;
	rep(i, 1, l) {
		ans += dp[n][i] * pow_(m, l - i) % MOD;
		ans %= MOD;
	}
	cout << ans << "\n";
	return 0;
}


