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
	random;
	vector<vector<int>> mp;
	vector<int> pre, dep, sz, mx;
	void init_(int _n) {
		n = _n;
		dep.assign(n + 1, 0);
		rep(i, 1, n) dep[i] = rnd() % 65536;
	}
	void dfs1(int x, int par) {
		sz[x] = 1;
		for(auto i : mp[x]) if(i != par) {
			dfs1(i, x);
			sz[x] += sz[i];
			mx[x] = max(mx[x], sz[i]);
		}
	}
	int dfs(int x, int par, int d) {
		int ans = 1;
		vector<int> v;
		for(auto i : mp[x]) if(i != par) {
			v.push_back(dfs(i, x, d + 1));
		}
		sort(all(v));
		int cur = dep[d];
		for(auto i : v) {
			ans = (ans + cur * i % MOD) % MOD;
			cur = cur * dep[d] % MOD;
		}
		if(!x) return 0;
		return ans;
	}
	pii get_pair() {
		mp.assign(n + 1, vector<int>());
		mx.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		rep(i, 1, n - 1) {
			int a, b;
			cin >> a >> b;
			mp[a].push_back(b);
			mp[b].push_back(a);
		}
		dfs1(1, 1);
		auto get_val = [&](int x) {
			return max(mx[x], n - sz[x]);
		};
		int a = 1, b = 0;
		rep(i, 2, n) {
			int cur = i;
			if(get_val(a) > get_val(cur)) swap(a, cur);
			if(get_val(b) > get_val(cur)) swap(b, cur);
		}
		return {dfs(a, a, 1), dfs(b, b, 1)};
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		pii a = get_pair();
		pii b = get_pair();
		if(a.x == b.x || a.x == b.y ||
			a.y == b.x || a.y == b.y) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}



