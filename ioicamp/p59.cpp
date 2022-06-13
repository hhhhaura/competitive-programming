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
namespace solver {
	int n;
	const int P = 1000000;
	vector<int> deg, dp, cnt;
	void init_(int _n) {
		n = _n;
		dp.assign(P + 1, 0);
		cnt.assign(P + 1, 0);
	}
	void solve() {
		int ans = 0;
		rep(i, 1, P) if(cnt[i]) {
			ans = max(ans, dp[i] + cnt[i]);
			for(int j = 2 * i; j <= P; j += i) {
				if(!cnt[j]) continue;
				dp[j] = max(dp[j], dp[i] + cnt[i]);
			}
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) {
		int x; cin >> x;
		cnt[x] ++;
	}
	solve();
	return 0;
}

