#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
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
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, m;
	vector<int> A, B;
	vector<vector<int>> dp, l, r;
	void init_(string a, string b) {
		A = {0}, B = {0};
		int yes = -1;
		rep(i, 0, signed(a.size()) - 1) if(a[i] == '0') yes = i;
		rep(i, yes + 1, signed(a.size()) - 1) {
			if(a[i] == '+') A.push_back(-1);
			else A.push_back(a[i] - '0');
		}
		n = A.size();
		yes = -1;
		rep(i, 0, signed(b.size()) - 1) if(b[i] == '0') yes = i;
		rep(i, yes + 1, signed(b.size()) - 1) {
			if(b[i] == '+') B.push_back(-1);
			else B.push_back(b[i] - '0');
		}
		m = B.size();
		l.assign(n + 1, vector<int>(m + 1, 0));
		r.assign(n + 1, vector<int>(m + 1, 0));
		dp.assign(n + 1, vector<int>(m + 1, 0));
	}
	void solve() {
		rep(i, 0, n) dp[i][m] = 1;
		rep(i, 0, m) dp[n][i] = 1;
		rrep(i, 1, n) rrep(j, 1, m) {
			if(i != n && j != m) {
				if((max(abs(A[i]), abs(B[j])) == 1 || 
					(A[i] != -1 && B[j] != -1))) {
					dp[i][j] = (dp[i + 1][j] 
						+ dp[i][j + 1] - dp[i + 1][j + 1]) % MOD;
				
				}
				else dp[i][j] = (dp[i + 1][j] + dp[i][j + 1]) % MOD;
			}
			if(i != n) l[i][j] = dp[i + 1][j];
			if(j != m) r[i][j] = dp[i][j + 1];
			print(i, j, l[i][j], r[i][j]);
		}
		int L = n, R = m;
		rrep(i, 0, n - 1) if(A[i] == -1) L = i;
		rrep(i, 0, m - 1) if(B[i] == -1) R = i;
		if(L == n && R == m) cout << "1\n";
		else {
			int ans = 0;
			print(L, R);
			if(L != n) rep(i, 1, R) ans = (ans + l[L][i]) % MOD;
			if(R != m) rep(i, 1, L) ans = (ans + r[i][R]) % MOD;
			if(L == n || R == m) ans ++;
			cout << ans << "\n";
		}
		
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		string a, b;
		cin >> a >> b;
		init_(a, b);
		solve();
	}
	return 0;
}

