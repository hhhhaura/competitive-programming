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
	vector<int> es, vis, ok;
	vector<pii> ans;
	vector<vector<int>> mp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		mp.assign(n + 1, vector<int>());
		es.assign(m, 0);
		vis.assign(m, 0);
		ok.assign(n + 1, 0);
	}
	void dfs(int x) {
		ok[x] = 1;
		for(auto i : mp[x]) if(!vis[i]) {
			int to = es[i] ^ x;
			vis[i] = 1;
			if(ok[to]) ans.push_back({to, x});
			else ans.push_back({x, to});
			if(!ok[to]) dfs(to);
		}
	}
};
using namespace solver;	
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 0, m - 1) {
		int x, y;
		cin >> x >> y;
		mp[x].push_back(i);
		mp[y].push_back(i);
		es[i] = x ^ y;
	}
	rep(i, 1, n) if(!ok[i]) dfs(i);
	for(auto i : ans) cout << i.x << " " << i.y << "\n"; 
	return 0;
}


