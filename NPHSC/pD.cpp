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
namespace solver {
	int n, m;
	const int P = 20000 + 137;
	string s;
	vector<bitset<P>> dp;
	vector<vector<int>> a;
	vector<char> ch = {'R', 'P', 'S'};
	void init_(int _n, int _m, string _s) {
		n = _n, m = _m, s = _s;
		dp.assign(m + 1, bitset<P>());
		a.assign(m + 1, vector<int>(3, 0));
	}
	void solve() {
		rep(i, 0, m - 1) {
			for(int j = i; j < n; j += m) {
				if(s[j] == 'R') a[i][1] ++, a[i][2] --;
				else if(s[j] == 'P') a[i][0] --, a[i][2] ++;
				else a[i][0] ++, a[i][1] --;
			}
		}	
		dp[0][n] = 1;
		rep(i, 0, m - 1) {
			bitset<P> cur;
			rep(j, 0, 2) {
				if(a[i][j] > 0) cur = cur | (dp[i] << a[i][j]);
				else cur = cur | (dp[i] >> -a[i][j]);
			}
			dp[i + 1] = cur;
		}
		int ans = -1;
		string t = "";
		rep(i, n + 1, 2 * n) if(dp[m][i]) {
			ans = i;
			break;
		}
		if(ans == -1) {
			cout << -1 << "\n";
			cout << "impossible\n";
			return;
		}
		int haha = ans;
		rrep(i, 1, m) {
			rep(j, 0, 2) {
				bitset<P> cur;
				if(a[i - 1][j] > 0) cur = (dp[i - 1] << a[i - 1][j]);
				else cur = (dp[i - 1] >> -a[i - 1][j]);
				if(cur[haha]) {
					t += ch[j];
					haha = haha - a[i - 1][j];
					break;
				}
			}
		}
		reverse(all(t));
		cout << ans - n << "\n";
		cout << t << "\n";

	}

	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		string s; cin >> s;
		init_(n, m, s);
		solve();
	}
	return 0;
}

