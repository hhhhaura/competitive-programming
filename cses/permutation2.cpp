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
void add(int &a, int b) {
	a = (a + b) % MOD;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<vector<int>> dp1(n + 2, vector<int>(n + 2, 0));
	vector<vector<int>> dp0(n + 2, vector<int>(n + 2, 0));
	dp0[1][0] = 1, dp1[2][1] = 2;
	rep(i, 2, n - 1) rep(j, 0, i - 1) {
		add(dp1[i + 1][j + 1], dp0[i][j] * 2ll % MOD);
		add(dp0[i + 1][j], dp0[i][j] * (i - 1 - j) % MOD);
		if(j) add(dp0[i + 1][j - 1], dp0[i][j] * j % MOD); 
		
		add(dp0[i + 1][j], dp1[i][j] * (i - j) % MOD);
		add(dp1[i + 1][j + 1], dp1[i][j]);
		add(dp1[i + 1][j], dp1[i][j]);
		if(j) add(dp0[i + 1][j - 1], dp1[i][j] * (j - 1) % MOD);
	}
	cout << dp0[n][0] << "\n";
	return 0;
}


