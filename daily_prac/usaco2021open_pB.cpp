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
	vector<vector<int>> a;
	vector<int> c, id, par, rk;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, vector<int>(4, 0));
		c.assign(n + 1, 0);
		id.assign(n, 0);
		iota(all(id), 1);
		par.assign(2 * n + 1, 0);
		iota(all(par), 0);
		rk.assign(2 * n + 1, 0);
	}
	int find_par(int a) {
		if(par[par[a]] == par[a]) return par[a];
		else return par[a] = find_par(par[a]);
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa]++;
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
	void solve() {
		rep(i, 1, n) {
			unite(a[i][0], a[i][1]);
			unite(a[i][2], a[i][3]);
		}
		sort(all(id), [&](int a, int b) {
			return c[a] < c[b];
		});
		int ans = 0;
		for(auto i : id) {
			if(same(a[i][1], a[i][2])) continue;
			ans += c[i];
			unite(a[i][1], a[i][2]);
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) {
		cin >> c[i];
		rep(j, 0, 3) cin >> a[i][j];
	}
	solve();
	return 0;
}

