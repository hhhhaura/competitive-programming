#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#pragma GCC target("sse")

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(a) a.begin(), a.end()
#define ceil(a, b) ((a + b - 1) / (b))

using namespace std;

#define int long long int
#define pii pair<int, int>
#define lld long double
#define eps (1e-9)
#define INF 1000000000000000000
#define MOD 1000000007
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<": ", kout("["+string(#a)+"] = ",a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m;
	vector<vector<int>> a, mp1, mp2, vis, mp, pari;
	vector<int> L, R, ok, par;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(m + 1, vector<int>());
		mp1.assign(n + 1, vector<int>());
		mp2.assign(n + 1, vector<int>());
		pari.assign(n + 1, vector<int>(n + 1, 0));
		vis.assign(m + 1, vector<int>(n + 1, 0));
		L.assign(n + 1, INF);
		R.assign(n + 1, 0);
		par.assign(n + 1, 0);
	}
	bool dfs(int x, bool yes) {
		ok[x] = 2;
		int ans = 1;
		for(auto i : mp[x]) {
			if(ok[i] == 2 || (yes && pari[x][i])) return 0;
			else if(ok[i] == 0) ans &= dfs(i, yes);
		}
		ok[x] = 1;
		return ans;
	}
	int solve() {
		rep(i, 1, m) {
			vector<int> v, col(n + 1, -1), tot;
			vector<vector<int>> ispar(n + 1, vector<int>(n + 1, 0));
			for(auto j : a[i]) {
				if(col[j] == -1) {
					col[j] = 1;
					L[j] = min(L[j], i);
					R[j] = max(R[j], i);
					vis[i][j] = 1;
					v.push_back(j);
					tot.push_back(j);
				}
				else {
					if(v.back() != j) return 0;
					v.pop_back();
					if(v.size()) {
						mp1[v.back()].push_back(j);
						if(par[j] && v.back() != par[j]) return 0;
						par[j] = v.back();
					}
				}
			}
			for(auto i : tot) {
				int cur = i;
				while(cur) {
					ispar[cur][i] = ispar[i][cur] = 1;
					pari[i][cur] = pari[cur][i] = 1;
					cur = par[cur];
				}
			}
			rep(j, 0, signed(a[i].size()) - 1) {
				col[a[i][j]] = j;
			}
			for(auto j : tot) for(auto k : tot) {
				if(ispar[j][k] || j == k) continue;
				int a = j, b = k;
				if(col[a] < col[b]) swap(a, b);
				mp2[a].push_back(b);
			}
		}
		rep(i, 1, n) {
			int yes = 1;
			rep(j, L[i], R[i]) yes &= vis[j][i];
			if(!yes) return 0;
		}
		mp = mp1;
		int ans = 1;
		ok.assign(n + 1, 0);
		rep(i, 1, n) if(!ok[i]) ans &= dfs(i, 0);
		mp = mp2;
		ok.assign(n + 1, 0);
		rep(i, 1, n) if(!ok[i]) ans &= dfs(i, 1);
		return ans;
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie();
	int t; cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		init_(n, m);
		rep(i, 1, m) {
			int x; cin >> x;
			rep(j, 1, x) {
				int y; cin >> y;
				a[i].push_back(y);
			}
		}
		if(solve()) cout << "YES\n";
		else cout << "NO\n";
	} 
	return 0; 
}
