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
	int n;
	vector<vector<int>> mp;
	vector<pii> a, b, ans, v;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		a.clear(), b.clear();
		ans.clear();
	}
	void dfs(int x, int par, int top) {
		int cnt = 0;
		for(auto i : mp[x]) if(i != par) {
			cnt ++, dfs(i, x, top);
		}
		if(!cnt) v.push_back({x, top});
	}
	void solve() {
		int rt = 0;
		rep(i, 1, n) if(mp[i].size() > 1) rt = i;
		for(auto i : mp[rt]) {
			v.clear();
			dfs(i, rt, i);
			if(v.size() > a.size()) {
				for(auto j : a) b.push_back(j);
				v.swap(a);
			}
			else for(auto j : v) b.push_back(j); 
		}
		while(a.size() < b.size()) {
			pii p = b.back(); b.pop_back();
			a.push_back(p);
		}
		reverse(all(a));	
		int mn = min(a.size(), b.size());
		cout << a.size() << "\n";
		rep(i, 0, mn - 1) {
			assert(a[i].y != b[i].y);
			cout << a[i].x << " " << b[i].x << "\n";  
		}
		rep(i, mn, signed(a.size()) - 1)
			cout << rt << " " << a[i].x << "\n";
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


