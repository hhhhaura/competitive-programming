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
	vector<int> par, rk, mx;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		par.assign(n + 1, 0);
		iota(all(par), 0);
		rk.assign(n + 1, 0);
		mx.assign(n + 1, 0);
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else rk[aa] ++, par[bb] = aa;
	}
	void solve() {
		int ii = 0;
		vector<int> vis(m + 1, 0), sum(n + 1, 1);
		vector<pii> es(m + 1, {0, 0});
		vector<pii> v(m + 1, {0, 0});
		rep(i, 1, m) {
			char c; cin >> c;
			if(c == 'D') {
				int x; cin >> x;
				v[i] = {1, x};
				sum[x] = 0;
			}
			else if(c == 'A') {
				int x, y;
				cin >> x >> y;
				es[++ii] = {x, y};
				v[i] = {2, ii};
			}
			else {
				int x; cin >> x;
				v[i] = {3, x};
				vis[x] = 1;
			}
		}
		rep(i, 1, m) if(!vis[i]) unite(es[i].x, es[i].y);
		rep(i, 1, n) if(sum[i]) {
			int p = find_par(i);
			mx[p] = m;
		}
		rrep(i, 1, m) {
			int tp = v[i].x, x = v[i].y;
			if(tp == 1) {
				int p = find_par(x);
				mx[p] = max(mx[p], i - 1);
			}
			else if(tp == 3) {
				int a = es[x].x, b = es[x].y;
				int aa = find_par(a);
				int bb = find_par(b);
				if(mx[aa] > mx[bb]) swap(aa, bb);
				if(mx[aa] && mx[bb]) continue;
				else if(mx[aa] == 0 && mx[bb]) mx[aa] = i - 1;
				else unite(a, b);
			}
		}
		rep(i, 1, n) cout << mx[find_par(i)] <<  "\n";

	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	solve();
	return 0;
}

