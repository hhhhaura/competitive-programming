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
	int n, m, lg;
	vector<int> par, sz, d;
	vector<vector<int>> ac, mx;
	vector<vector<pii>> mp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		lg = 31 - __builtin_clz(n);
		par.assign(n + 1, 0);
		iota(all(par), 0);
		sz.assign(n + 1, 1);
		d.assign(n + 1, 0);
		mp.assign(n + 1, vector<pii>());
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		mx.assign(lg + 1, vector<int>(n + 1, 0));
	}
	int find_par(int x) {
		while(x != par[x]) x = par[x];
		return x;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		sz[aa] += sz[bb];
		par[bb] = aa;
	}
	void dfs(int x, int par, int dd = 0) {
		for(auto i : mp[x]) if(i.x != par) {
			ac[0][i.x] = x;
			mx[0][i.x] = i.y;
			d[i.x] = dd + 1;
			dfs(i.x, x, dd + 1);
		}
	}
	void build() {
		rep(i, 1, n) if(!ac[0][i]) dfs(i, i);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
			mx[i][j] = max(mx[i - 1][j], mx[i - 1][ac[i - 1][j]]);
		}
	}
	int LCA(int a, int b) {
		if(d[a] < d[b]) swap(a, b);
		int need = d[a] - d[b];
		rep(i, 0, lg) if((need >> i) & 1) a = ac[i][a];
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a], b = ac[i][b];
		}
		return ac[0][a];
	}
	int get_mx(int a, int v) {
		int val = 0;
		rep(i, 0, lg) if((v >> i) & 1) {
			val = max(val, mx[i][a]);
			a = ac[i][a];
		}
		return val;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	init_(n, q);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		if(find_par(a) != find_par(b)) {
			unite(a, b);
			mp[a].push_back({b, i});
			mp[b].push_back({a, i});
		} 
	}
	build();
	rep(i, 1, q) {
		int a, b;
		cin >> a >> b;
		int lca = LCA(a, b);
		if(find_par(a) != find_par(b)) cout << "-1\n";
		else cout << max(get_mx(a, d[a] - d[lca])
			, get_mx(b, d[b] - d[lca])) << "\n";
	}
	return 0;
}



