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

signed main() {
	int tt = 0;
	string s, t;
	while(tt++, getline(cin, s) && s != "#") {
		getline(cin, t);
		int n = s.size(), m = t.size();
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
		rep(i, 0, n) rep(j, 0, m) {
			if(i && j && s[i - 1] == t[j - 1]) 
				dp[i][j] = dp[i - 1][j - 1] + 1;
			if(i) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			if(j) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
		}
		cout << "Case #" << tt << ": you can visit at most "<< 
			dp[n][m] << " cities.\n";
	}
	return 0;
}

