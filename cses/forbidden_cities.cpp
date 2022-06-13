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
	int n, q, ii, id, timestamp, lg;
	vector<int> L, D, pre, dep;
	vector<vector<int>> mp1, mp2;
	vector<vector<int>> ac;
	void init_(int _n, int _q) {
		n = _n, ii = 0;
		timestamp = 0;
		id = n, q = _q;
		lg = 31 - __builtin_clz(2 * n);
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		dep.assign(n * 2 + 1, 0);
		mp1.assign(n + 1, vector<int>());
		mp2.assign(n * 2 + 1, vector<int>());
		ac.assign(lg + 1, vector<int>(n * 2 + 1, 0));
	}
	void dfs(int x, int par) {
		pre[ii++] = x;
		L[x] = D[x] = ++timestamp;
		for(auto i : mp1[x]) if(i != par) {
			if(!D[i]) {
				dfs(i, x);
				L[x] = min(L[x], L[i]);
				if(L[i] >= D[x]) {
					id ++;
					mp2[x].push_back(id);
					mp2[id].push_back(x);
					while(pre[ii] != i) {
						ii--;
						mp2[pre[ii]].push_back(id);
						mp2[id].push_back(pre[ii]);
					}
				}
			}
			else if(D[i] < D[x]) L[x] = min(L[x], D[i]);
		}
	}
	void dfs1(int x, int par, int d) {
		ac[0][x] = par;
		dep[x] = d;
		for(auto i : mp2[x]) if(i != par) {
			dfs1(i, x, d + 1);
		}
	}
	int LCA(int a, int b) {
		if(dep[a] < dep[b]) swap(a, b);
		int need = dep[a] - dep[b];
		rrep(i, 0, lg) if((need >> i) & 1)
			a = ac[i][a];
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a], b = ac[i][b];
		}
		return ac[0][a];
	}
	void solve() {
		dfs(1, 1);
		dfs1(1, 1, 0);
		rep(i, 1, lg) rep(j, 1, id) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
		rep(i, 1, q) {
			int a, b, c;
			cin >> a >> b >> c;
			int lca = LCA(a, b);
			if((LCA(a, c) == lca && LCA(b, c) == c) ||
				(LCA(b, c) == lca && LCA(a, c) == c)) cout << "NO\n";
			else cout << "YES\n";
		}
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
		mp1[a].push_back(b);
		mp1[b].push_back(a);
	}
	solve();
	return 0;
}


