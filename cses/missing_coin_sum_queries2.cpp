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
	int n, q, lg;
	const int P = 30;
	vector<vector<int>> mn;
	vector<pii> v;
	vector<int> ans, a, pre;
	void init_(int _n, int _q) {
		n = _n, q = _q;
		lg = 31 - __builtin_clz(n);
		v.assign(q, {0, 0});
		ans.assign(q, 0);
		a.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		mn.assign(lg + 1, vector<int>(n + 1, 0));
	}
	int query(int L, int R) {
		int pos = 31 - __builtin_clz(R - L + 1);
		return min(mn[pos][L], mn[pos][R - (1 << pos) + 1]);
	}
	void operate(int id) {
		mn.assign(lg + 1, vector<int>(n + 1, 0));
		pre.assign(n + 1, 0);
		rep(i, 1, n) {
			int pos = 31 - __builtin_clz(a[i]);
			pre[i] = pre[i - 1];
			if(pos == id) {
				mn[0][i] = a[i];
				pre[i] += a[i];
			}
			else mn[0][i] = INF;
		}
		rep(i, 1, lg) rep(j, 1, n) {
			int to = j + (1 << (i - 1));
			if(to <= n) mn[i][j] = min(mn[i - 1][j], mn[i - 1][to]);
			else mn[i][j] = mn[i - 1][j];
		}
		rep(i, 0, q - 1) {
			int l = v[i].x, r = v[i].y;
			int val = query(l, r);
			if(ans[i] + 1 >= val) ans[i] += pre[r] - pre[l - 1];
		}
		return;
	}
	void solve() {
		rep(i, 0, P) operate(i);
		rep(i, 0, q - 1) cout << ans[i] + 1 << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n, q);
	rep(i, 1, n) cin >> a[i];
	rep(i, 0, q - 1) cin >> v[i].x >> v[i].y;
	solve();
	return 0;
}


