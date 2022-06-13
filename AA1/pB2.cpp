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
	int t; cin >> t;
	while(t--) {
		int n, L, K;
		cin >> n >> L >> K;
		vector<vector<int>> pre(n + 2, vector<int>(n + 2, 0));
		vector<vector<int>> cnt(n + 2, vector<int>(n + 2, 0));
		vector<vector<int>> dp(n + 2, vector<int>(K + 1, -INF));
		vector<int> d(n + 1, 0), h(n + 1, 0);
		rep(i, 1, n) cin >> d[i] >> h[i];
		cnt[0][n + 1] = INF;
		rep(i, 1, n) {
			int cur = h[i] + d[i] - 1;
			int a = 0;
			rep(j, 1, i) a += ((cur - d[j] + 1) > h[j]);
			pre[0][i] = (cur + h[i]) * d[i] / 2;
			cnt[0][i] = a;
		}
		rep(i, 1, n) {
			int a = 0, to = (L - d[i]) + h[i];
			rep(j, i, n) a += (h[i] + d[j] - d[i] > h[j]);
			pre[i][n + 1] = (to + h[i] + 1) * (L - d[i]) / 2;
			cnt[i][n + 1] = a;
			
		}
		rep(i, 1, n) rep(j, i + 1, n) {
			if(d[j] - d[i] < abs(h[j] - h[i])) {
				cnt[i][j] = INF;
				continue;
			}
			int a = 0, to = (h[j] - h[i] + d[j] - d[i]);
			int b = to / 2, fin = h[i] + b - (d[j] - d[i] - b);
			rep(k, i + 1, j) {
				int val = d[k] - d[i];
				int cur = (val <= b ? h[i] + val : 
					h[i] + 2ll * b - val + (to & 1));
				a += (cur > h[k]);
			}
			pre[i][j] += (2ll * h[i] + 1 + b) * b / 2;
			pre[i][j] += (h[i] + b - 1 + fin + 2 * (to & 1)) 
				* (d[j] - d[i] - b) / 2; 
			cnt[i][j] = a;
		}
		dp[0][0] = 0;
		rep(i, 1, n + 1) rep(j, 0, K) {
			int to = 0, best = 0;
			rep(k, 0, i - 1) if(cnt[k][i] <= j) {
				int val = dp[k][j - cnt[k][i]] + pre[k][i];
				if(val > best) to = k, best = val;
				dp[i][j] = max(dp[i][j], dp[k][j - cnt[k][i]] + pre[k][i]);
			
			}
		}
		int ans = 0;
		rep(i, 0, K) ans = max(ans, dp[n + 1][i]);
		cout << ans << "\n";
	}
	return 0;
}

/*
1
10 10 7
1 9
2 2
3 8
4 10
5 3
6 8
7 4
8 10
9 3
10 4
*/
