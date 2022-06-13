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
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count)

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
	int n, l, K;
	const int mx = 500; 
	vector<int> d, v;
	vector<vector<int>> cur, nxt;
	void init_(int _n, int _l, int _k) {
		n = _n, l = _l, K = _k;
		cur.assign(mx + 5, vector<int>(K + 5, -INF));
		d.assign(n + 1, 0);
		v.assign(n + 1, 0);
	}
	void solve() {
		rep(i, 1, mx) if(K - (v[1] < i) >= 0)cur[i][K - (v[1] < i)] = i;
		int ans = 0;
		rep(i, 2, n) {
			nxt.assign(mx + 5, vector<int>(K + 5, -INF));
			rep(j, 1, mx) rep(k, 0, K) {
				bool yes = j > v[i];
				nxt[j][k] = cur[j][k + yes] + j;
				if(j > 1) nxt[j][k] = max(nxt[j][k], cur[j - 1][k + yes] + j);
				if(j < mx) nxt[j][k] = max(nxt[j][k], cur[j + 1][k + yes] + j);
			}
			nxt.swap(cur);
		} 
		rep(i, 1, mx) rep(j, 0, K) ans = max(ans, cur[i][j]);
		cout << ans << "\n";
		
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n, l, k;
		cin >> n >> l >> k;
		init_(n, l, k);
		rep(i, 1, n) cin >> d[i] >> v[i];
		solve();
	}
	return 0;
}


