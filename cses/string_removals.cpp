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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s; cin >> s;
	int n = s.size();
	vector<vector<int>> pos(26, vector<int>());
	vector<int> dp(n, 0);
	rrep(i, 0, n - 1) pos[s[i] - 'a'].push_back(i);
	rep(i, 0, 25) if(pos[i].size()) 
		dp[pos[i].back()] = 1;
	int ans = 0;
	rep(i, 0, n - 1) {
		int cur = s[i] - 'a';
		pos[cur].pop_back();
		ans = (ans + dp[i]) % MOD;
		rep(j, 0, 25) if(pos[j].size()) {
			int to = pos[j].back();
			dp[to] += dp[i];
			dp[to] %= MOD;
		}
	}
	cout << ans << "\n";
	return 0;
}


