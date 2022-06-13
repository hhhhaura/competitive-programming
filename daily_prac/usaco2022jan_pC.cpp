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
	int n, timestamp, h;
	vector<vector<int>> mp;
	vector<int> dep, val;
	void init_(int _n) {
		n = _n, timestamp = n + 1, h = 0;
		mp.assign(n + 2, vector<int>());
		dep.assign(n + 2, 0);
		val.assign(n + 2, 0);
	}
	void dfs(int x, int d) {
		dep[x] = d;
		val[x] = --timestamp;
		h = max(h, d);
		reverse(all(mp[x]));
		for(auto i : mp[x]) dfs(i, d + 1);
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	int k = n + 1;
	cout << n + 1 << "\n";
	rep(i, 1, n) {
		int x; cin >> x;
		mp[x + 1].push_back(i);
	}
	dfs(n + 1, 0);
	rep(i, 1, n) cout << k * (h - dep[i]) + val[i] << "\n";
	
	return 0;
}


