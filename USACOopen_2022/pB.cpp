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
	random;
	vector<int> A, B;
	vector<vector<int>> dp;
	const pii MOD = {1000000007, 998244353};
	vector<pii> val; 
	vector<vector<pii>> suf;
	pii mul(pii a, pii b) {
		return {a.x * b.x % MOD.x, a.y * b.y % MOD.y};	
	}
	void init_(string a, string b) {
		int yes = 0;
		A.clear();
		B.clear();
		for(auto i : a) {
			if(i == '+') {
				yes = 1;
				A.push_back(-1);
			}
			if(yes) A.push_back(i - '0');
		}
		for(auto i : b) {
			if(i == '+') {
				yes = 1;
				B.push_back(-1);
			}
			if(yes) B.push_back(i - '0');
		}
		n = A.size();
		m = B.size();
		dp.assign(n + 1, vector<int>(m + 1, 0));
		suf.assign(n + 1, vector<pii>(m + 1, {0, 0}));
		val.assign(10, {0, 0});
		val[1] = {1, 1};
		val[2] = {rnd(), rnd()};
		val[3] = {rnd(), rnd()};
		val[4] = mul(val[2], val[2]);
		val[5] = {rnd(), rnd()};
		val[6] = mul(val[3], val[2]);
		val[7] = {rnd(), rnd()};
		val[8] = mul(val[4], val[2]);
		val[9] = mul(val[3], val[3]);
	}
	void solve() {
		suf[n][m] = val[1];
		rrep(i, 0, n) rrep(j, 0, m) {
			if(i != n) suf[i][j] = mul(suf[i + 1][j], val[abs(A[i])]);
			if(j != m) suf[i][j] = mul(suf[i][j + 1], val[abs(B[j])]);
		}
		dp[n][m] = 1;
		rep(i, 0, n) dp[i][m] = 1;
		rep(i, 0, m) dp[n][i] = 1;
		rrep(i, 0, n - 1) rrep(j, 0, m - 1) {
			pii L = suf[i + 1][j], R = suf[i][j + 1];
			if(A[i] * B[j] > 0) dp[i][j] = dp[i + 1][j + 1];
			else if(A[i] == 0 || B[j] == 0) dp[i][j] = 1 + 
				bool(A[i] != 0 || B[j] != 0);
			else if(A[i] == -1) {
				dp[i][j] = (dp[i][j] + dp[i + 1][j]) % MOD;
				if(B[j] != 1) dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD; 
			}
			else {
				assert(B[j] == -1);
				dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD;
				if(A[i] != 1) dp[i][j] = (dp[i][j] + dp[i + 1][j]) % MOD;
			}
		}
		cout << dp[0][0] << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);

	return 0;
}
