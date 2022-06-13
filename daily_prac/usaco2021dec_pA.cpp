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
	int t, n, k;
	cin >> t >> n >> k;
	vector<int> w(n + 2, 0), pos(n + 2, -INF);
	rep(i, 1, n) cin >> pos[i] >> w[i];
	auto solve = [&](int L, int R, int tp) {
		vector<int> dp[2];
		dp[0].assign(R - L + 2, -INF);
		dp[1].assign(R - L + 2, -INF);
		int l = L - 2;
		vector<int> val[2];
		val[0].assign(2, -INF);
		val[1].assign(2, -INF);
		dp[0][0] = 0;
		rep(i, L, R) {
			while(l + 1 < i && pos[i] - pos[l + 1] > k) {
				l++;
				val[l & 1][0] = max(val[l & 1][0], dp[0][l - L + 1]);
				val[l & 1][1] = max(val[l & 1][1], dp[1][l - L + 1]);
			}
			if(i < R && pos[i + 1] - pos[i - 1] <= k) {
				dp[1][i - L + 1] = max(val[i & 1][0] + tp * w[i],
					val[!(i & 1)][1] + tp * w[i]);
			}
			dp[0][i - L + 1] = max(val[!(i & 1)][0] + tp * w[i],	
				val[i & 1][1] + tp * w[i]);
		}
		int ans = -INF, len = R - L + 1;
		rep(i, 0, R - L + 1) {
			if((len - i) % 2 == 0) ans = max(ans, dp[0][i]);
			else ans = max(ans, dp[1][i]);
		}
		return ans * tp;
	};	
	int ans = 0, pre = 1, tp = (t == 1 ? -1 : 1);
	rep(i, 2, n + 1) {
		if(pos[i] - pos[i - 1] > k || i == n + 1) {
			ans += solve(pre, i - 1, tp);
			pre = i;
		}
	}
	cout << ans << "\n";
	return 0;
}

