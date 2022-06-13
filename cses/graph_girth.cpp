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
#define x first
#define y second
namespace solver {
	int n, m;
	vector<int> dp, pre;
	vector<vector<int>> mp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		pre.assign(n + 1, 0);
		dp.assign(n + 1, INF);
		mp.assign(n + 1, vector<int>());
	}
	int calculate(int s) {
		dp.assign(n + 1, INF);
		pre.assign(n + 1, 0);
		dp[s] = 0;
		queue<int> q;
		q.push(s);
		int ans = INF;
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) {
				if(dp[i] != INF && pre[cur] != i) 
					ans = min(ans, dp[cur] + dp[i] + 1);
				else if(dp[i] == INF){
					dp[i] = dp[cur] + 1;
					pre[i] = cur;
					q.push(i);
				}
			}
		}
		return ans;
	} 
	void solve() {
		int ans = INF;
		rep(i, 1, n) ans = min(ans, calculate(i));
		if(ans == INF) cout << "-1\n";
		else cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	solve();
	return 0;
}


