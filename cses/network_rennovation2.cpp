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
namespace solver {
	int n;
	vector<vector<int>> mp;
	vector<int> v;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		v.clear();
	}
	void dfs(int x, int par) {
		int cnt = 0;
		for(auto i : mp[x]) if(i != par) {
			cnt ++, dfs(i, x);
		}
		if(!cnt) v.push_back(x);
	}
	void solve() {
		int rt = 0;
		rep(i, 1, n) if(mp[i].size() > 1) rt = i;
		dfs(rt, rt);
		cout << ceil(v.size(), 2) << "\n";
		int h = ceil(v.size(), 2);
		rep(i, 0, signed(v.size()) / 2 - 1) {
			cout << v[i] << " " << v[i + h] << "\n";
		}
		if(v.size() & 1) cout << v[h - 1] << " " << rt << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	solve();
	return 0;
}


