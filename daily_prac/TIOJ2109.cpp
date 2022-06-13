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
	const int P = 1000;
	vector<int> dp(P + 1, -1);
	dp[1] = 1, dp[2] = 1, dp[0] = 0;
	rep(i, 3, P) {
		vector<int> ans;
		rep(j, 1, i) {
			int L = max(0ll, j - 3);
			int R = min(i + 1, j + 3);
			ans.push_back(dp[L] ^ dp[i - R + 1]);
		}
		sort(all(ans));
		ans.resize(unique(all(ans)) - ans.begin());
		rep(j, 0, signed(ans.size()) - 1) {
			if(j != ans[j]) {
				dp[i] = j;
				break;
			}
		}
		if(dp[i] == -1) dp[i] = ans.size();
	}
	dp[2] = 0;
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		int mx = 0;
		vector<int> a(n + 1, 0);
		rep(i, 1, n) {
			cin >> a[i];
			mx = max(mx, a[i]);
		}
		if(mx < 3) cout << "Draw\n";
		else {
			int ans = 0;
			rep(i, 1, n) ans ^= dp[a[i]];
			if(ans) cout << "First\n";
			else cout << "Second\n";
		}


	}
	return 0;
}


