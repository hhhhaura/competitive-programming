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
	int n, m, ii;
	const int P = 50;
	vector<int> vis, lst, par;
	vector<bitset<P>> pa, to;
	vector<vector<int>> mp1, mp2;
	void init_(int _n, int _m) {
		n = _n, m = _m, ii = 0;
		vis.assign(n, 0);
		lst.assign(n, 0);
		par.assign(n, -2);
		to.assign(n, bitset<P>());
		pa.assign(n, bitset<P>());
		mp1.assign(P, vector<int>());
		mp2.assign(P, vector<int>());
	}
	bool dfs(int x, vector<bitset<P>> &dp, 
		vector<vector<int>> &mp) {
		vis[x] = -1;
		int ans = 1;
		for(auto i : mp[x]) if(ans){
			dp[i] |= dp[x], dp[i][x] = 1;
			if(vis[i] == -1) return 0;
			else if(vis[i] != ii) ans &= dfs(i, dp, mp);
		}
		vis[x] = ii;
		return ans;
	}
	void solve() {
		int bad = 0;
		rep(i, 1, m) {
			int k; cin >> k;
			vector<int> L(n, INF), R(n, 0), vis(n, 0), fa(n, -1);
			rep(j, 1, k) {
				int x; 
				cin >> x, x--;
				L[x] = min(L[x], j);
				R[x] = max(R[x], j);
				vis[x] = 1;
				if(lst[x] == 0 || lst[x] + 1 >= i) lst[x] = i;
				else bad = 1;
			}
			rep(x, 0, n - 1) rep(y, 0, n - 1) if(x != y) {
				if(!vis[x] || !vis[y]) continue;
				if(L[x] < L[y] && R[x] > R[y]) {
					if(fa[y] == -1 ||  L[fa[y]] < L[x]) fa[y] = x;
					mp1[x].push_back(y);
				}
				if(L[x] > R[y]) mp2[x].push_back(y);
				if(L[y] < R[x] && L[x] < L[y] && R[x] < R[y]) bad = 1;
			}
			rep(j, 0, n - 1) if(vis[j]) {
				if(par[j] == -2) par[j] = fa[j];
				else if(par[j] != fa[j]) bad = 1;
			}
		}
		ii++;
		if(bad) {
			cout << "NO\n";
			return;
		}
		int ans = 1;
		rep(i, 0, n - 1) if(vis[i] != ii) {
			ans &= dfs(i, pa, mp1);
			if(!ans) {
				cout << "NO\n";
				return;
			}
		}
		ii++;
		rep(i, 0, n - 1) if(vis[i] != ii) {
			ans &= dfs(i, to, mp2);
			if(!ans) {
				cout << "NO\n";
				return;
			}
		}
		rep(i, 0, n - 1) rep(j, i + 1, n - 1) {
			if((to[i][j] || to[j][i]) 
				&& (pa[i][j] || pa[j][i])) {
				cout << "NO\n";
				return;
			}
		} 
		cout << "YES\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		init_(n, m);
		solve();
	}
	return 0;
}

