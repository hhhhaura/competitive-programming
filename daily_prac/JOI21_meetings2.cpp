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
	int n, lg;
	vector<vector<int>> mp, ac;
	vector<int> dep, sz, mx, ans;
	void init_(int _n) {
		n = _n;
		lg = 31 - __builtin_clz(n);
		dep.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		ans.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		mp.assign(n + 1, vector<int>());
	}
	void get_info(int x, int par) {
		sz[x] = 1;
		for(auto i : mp[x]) if(i != par) {
			get_info(i, x);
			sz[x] += sz[i];
			mx[x] = max(mx[x], sz[i]);
		}
	}
	void dfs(int x, int par, int d) {
		dep[x] = d;
		sz[x] = 1;
		ac[0][x] = par;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x, d + 1);
			sz[x] += sz[i];
		}
	}
	int LCA(int a, int b) {
		if(dep[a] < dep[b]) swap(a, b);
		int need = dep[a] - dep[b];
		rrep(i, 0, lg) if((need >> i) & 1)
			a = ac[i][a];
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a];
			b = ac[i][b];
		}
		return ac[0][a];
	}
	int dis(int a, int b) {
		return dep[a] + dep[b] - 2ll * dep[LCA(a, b)];
	}
	void solve() {
		get_info(1, 1);
		int cen = 1;
		rep(i, 2, n) if(max(mx[i], n - sz[i]) < 
			max(mx[cen], n - sz[cen])) cen = i;
		dfs(cen, cen, 0);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		} 
		vector<int> a(n, 0);
		iota(all(a), 1);
		sort(all(a), [&](int a, int b){
			return sz[a] > sz[b];
		});
		int L = cen, R = cen;
		for(auto i : a) if(i != cen) {
			int len = dis(L, R);
			if(dis(L, i) > len) R = i;
			else if(dis(R, i) > len) L = i;
			ans[sz[i]] = max(ans[sz[i]], dis(L, R));
		}
		rrep(i, 1, n - 1) ans[i] = max(ans[i], ans[i + 1]) ;
		rep(i, 1, n) {
			if(i & 1) cout << 1 << "\n";
			else cout << ans[i / 2] + 1 << "\n";
		}
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

