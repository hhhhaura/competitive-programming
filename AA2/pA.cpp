#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__, kout("["+string(#a)+"] = ", a)
void kout() { cerr << endl; }
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, t, ii;
	const int P = 1000000;
	vector<int> par, rk, cnt, to, id, v;
	void init_(int _n, int _t) {
		n = _n, t = _t, ii = n;
		par.assign(P + 1, 0);
		rk.assign(P + 1, 0);
		cnt.assign(P + 1, 0);
		to.assign(n + 1, 0);
		id.assign(P + 1, 0);
		v.assign(n + 1, 0);
		rep(i, 1, n) {
			to[i] = i;
			cnt[i] = 1;
		}
		rep(i, 1, P) par[i] = i;
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void unite(int a, int b, int val) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] < rk[bb]) swap(aa, bb);
		rk[aa] += (rk[aa] == rk[bb]);
		cnt[aa] += cnt[bb];
		par[bb] = aa;
		v[id[aa]] = 0, v[id[bb]] = 0; 
		id[aa] = val;
		v[val] = aa;
	}
	void solve() {
		rep(i, 1, t) {
			int tp; cin >> tp;
			if(tp == 1) {
				int x, y; cin >> x >> y;
				int val = id[find_par(to[y])];
				unite(to[x], to[y], val);
			}
			else if(tp == 2) {
				int x, y; cin >> x >> y;
				int p = find_par(to[x]);
				cnt[p] --;
				to[x] = ++ii, cnt[ii] = 1;
				int val = id[find_par(to[y])];
				unite(to[x], to[y], val);
			}
			else if(tp == 3) {
				int x, y; cin >> x >> y;
				int p = find_par(to[x]);
				cnt[p] --;
				to[x] = ++ii, cnt[ii] = 1;
				if(!v[y]) v[y] = to[x], id[to[x]] = y;
				else unite(v[y], to[x], y);
			}
			else if(tp == 4) {
				int x; cin >> x;
				int p = find_par(to[x]);
				cout << id[p] << " " << cnt[p] << "\n";
			}
			else {
				int x; cin >> x;
				cout << cnt[v[x]] << "\n";
			}
		}
		rep(i, 1, n) {
			int p = find_par(to[i]);
			cout << id[p] << " \n"[i == n];
		} 
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int x;
	rep(i, 1, 5) cin >> x;
	int n, t;
	cin >> n >> t;
	init_(n, t);
	rep(i, 1, n) {
		int a; cin >> a;
		if(!v[a]) v[a] = i, id[i] = a;
		else unite(v[a], to[i], a);
	}
	solve();
	return 0;
}


