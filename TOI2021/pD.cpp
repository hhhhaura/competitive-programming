#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("O3,fast-math,unroll-loops,Ofast")
#pragma loop-opt(on)
#pragma GCC target("sse")
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, lg, m;
	int P = 60;
	struct edge { int to, w, a, b, p; };
	vector<vector<edge>> mp;
	vector<vector<int>> ac, up[60], down[60];
	vector<int> dep, v;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		lg = 31 - __builtin_clz(n);
		v.assign(lg + 1, 0);
		mp.assign(n + 1, vector<edge>());
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		rep(i, 0, P - 1) {
			up[i].assign(lg + 1, vector<int>(n + 1, 0));
			down[i].assign(lg + 1, vector<int>(n + 1, 0));
		}
		dep.assign(n + 1, 0);
	}
	void dfs(int x, int par, int d) {
		ac[0][x] = par;
		dep[x] = d;
		for(auto i : mp[x]) if(i.to != par) {
			rep(j, 0, P - 1) {
				int rem = j % i.p;
				up[j][0][i.to] = i.w + (i.b - rem + i.p) % i.p;
				down[j][0][i.to] = i.w + (i.a - rem + i.p) % i.p;
			}
			dfs(i.to, x, d + 1);
		}	
	}
	int LCA(int a, int b) {
		if(dep[a] < dep[b]) swap(a, b);
		int need = dep[a] - dep[b];
		rep(i, 0, lg) if((need >> i) & 1)
			a = ac[i][a];
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a], b = ac[i][b];
		}
		return ac[0][a];
	}
	void solve() {
		dfs(1, 1, 0);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
			int gogo = ac[i - 1][j];
			rep(k, 0, P - 1) {
				int a = (up[k][i - 1][j] + 1);
				int b = (down[k][i - 1][gogo] + 1);
				up[k][i][j] = up[(a + k) % P][i - 1][gogo] + a;
				down[k][i][j] = b + down[(b + k) % P][i - 1][j];
			}
		}
		while(m --) {
			int hr, mn, s, t;
			cin >> hr >> mn >> s >> t;
			mn = (mn + hr * 60) % P;
			int lca = LCA(s, t), ans = 0;
			int L = dep[s] - dep[lca];
			int R = dep[t] - dep[lca];
			rep(i, 0, lg) if((L >> i) & 1) {
				int val = up[mn][i][s] + 1;
				ans += val, mn = (mn + val) % P;
				s = ac[i][s];
			}
			if(s == t) cout << ans - 1 << "\n";
			else {
				rep(i, 0, lg) if((R >> i) & 1) {
					v[i] = t;
					t = ac[i][t];
				}
				rrep(i, 0, lg) if((R >> i) & 1) {
					int val = down[mn][i][v[i]] + 1;
					ans += val, mn = (mn + val) % P;
				}
				ans -= 1;
				cout << ans << "\n";
			}
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	int xx = 1;
	rep(i, 1, n - 1) {
		int x, y, w, a, b, p;
		cin >> x >> y >> w;
		cin >> a >> b >> p;
		mp[x].push_back({y, w, a, b, p});
		mp[y].push_back({x, w, b, a, p});
		int to = __gcd(xx, p);
		xx = xx * p / to;
	}
	P = xx;
	solve();
	return 0;
}


