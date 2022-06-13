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
	int n, timestamp;
	vector<vector<int>> mp;
	vector<int> vis, dp;
	vector<pii> ans;
	void init_(int _n) {
		n = _n, timestamp = 0;
		mp.assign(n + 1, vector<int>());
		vis.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		ans.clear();	
	}
	void dfs(int x, int par) {
		vis[x] = ++timestamp;
		for(auto i : mp[x]) if(i != par) {
			if(vis[i] > vis[x]) continue;
			if(!vis[i]) dfs(i, x);
			if(vis[i] < vis[x]) dp[x] ^= 1, ans.push_back({x, i});
			else if(dp[i]) ans.push_back({i, x});
			else dp[x] ^= 1, ans.push_back({x, i});
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	if(m & 1) cout << "IMPOSSIBLE\n";
	else {
		rep(i, 1, n) if(!vis[i]) {
			dfs(i, i);
			if(ans.size() & 1) {
				cout << "IMPOSSIBLE\n";
				return 0;
			}
		}
		for(auto i : ans) cout << i.x << " " << i.y << "\n";
	}
	return 0;
}


