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
	int n, k;
	vector<int> a, pre, cnt;
	vector<vector<int>> cost, dp;
	struct seg { int id, l, r; };
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		cost.assign(n + 1, vector<int>(n + 1, INF));
		dp.assign(n + 1, vector<int>(n + 1, INF));
	}
	int search(int a, int b, int L, int R, vector<int>&v) {
		while(R - L > 1) {
			int mid = (L + R) / 2;
			if(v[a] + cost[a][mid] 
				> v[b] + cost[b][mid]) R = mid;
			else L = mid;
		}
		return R;
	}
	void solve() {
		dp[0][0] = 0;
		rep(i, 1, n) {
			pre[i] = pre[i - 1] + i * a[i];
			cnt[i] = cnt[i - 1] + a[i];
		}
		rep(i, 0, n) cost[i][i] = 0;
		rep(i, 1, n) cost[0][i] = cnt[i] * i - pre[i];
		rep(i, 1, n) rep(j, i + 1, n) {
			int mid = (i + j) / 2;
			cost[i][j] = pre[mid] * 2 - pre[i - 1] - pre[j]
				- (cnt[mid] - cnt[i - 1]) * i + (cnt[j] - cnt[mid]) * j;
		}
		rep(i, 1, k) {
			vector<seg> v(n + 1, {0, 0, 0});
			int L = 0, R = 0;
			v[0] = {i - 1, i, n};
			rep(j, i, n) {
				while(v[L].r < j) L ++;
				int from = v[L].id;
				dp[i][j] = dp[i - 1][from] + cost[from][j];
				while(L <= R && dp[i - 1][v[R].id] + cost[v[R].id][v[R].l] >
					dp[i - 1][j] + cost[j][v[R].l]) R--;
				assert(L <= R);
				int to = search(v[R].id, j, v[R].l, v[R].r + 1, dp[i - 1]);
				v[R].r = to - 1;
				v[++R] = {j, to, n};
			}
		}
		int ans = INF;
		rep(i, k, n) ans = min(ans, dp[k][i] + 
			pre[n] - pre[i - 1] - (cnt[n] - cnt[i - 1]) * i);
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) cin >> a[i];
	solve();
	return 0;
}


