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
	int n, m; cin >> n;
	string s; cin >> s;
	m = s.size();
	vector<int> f(m + 2, -1);
	vector<vector<int>> dp1(n + 2, vector<int>(m + 2, 0));
	vector<vector<int>> dp2(n + 2, vector<int>(m + 2, 0));
	rep(i, 1, m - 1) {
		int pre = f[i - 1];
		while(pre != -1 && s[pre + 1] != s[i]) pre = f[pre];
		if(s[pre + 1] == s[i]) pre ++;
		f[i] = pre;
	}
	dp1[0][0] = 1;
	auto add = [&](int &a, int b) {
		a = (a + b) % MOD;
	};
	rep(i, 0, n - 1) rep(j, 0, m) {
		rep(k, 0, 25) {
			int cur = j - 1;
			while(cur != -1 && s[cur + 1] - 'A' != k) cur = f[cur];
			if(s[cur + 1] - 'A' == k) cur ++;
			if(cur + 1 == m) add(dp2[i + 1][cur + 1], dp1[i][j]);
			else add(dp1[i + 1][cur + 1], dp1[i][j]);
			add(dp2[i + 1][cur + 1], dp2[i][j]);
		}
	}
	int ans = 0;
	rep(i, 0, m) add(ans, dp2[n][i]);
	cout << ans << "\n";
	return 0;
}


