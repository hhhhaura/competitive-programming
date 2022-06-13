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
	int n, lg = 32;
	vector<int> a, b;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
	}
	int best(int L, int R, int id) {
		if(R >= 0) return 0;
		L *= -1, R *= -1, swap(L, R);
		int ans = 0, v = (1ll << id), yes = 0;
		int a = (L & R), b = (L ^ R), best = INF;
		rrep(i, 0, 62) {
			int val = (1ll << i);
			int ok = (yes ? (L >> i) & 1 : (a >> i) & 1);
			int cost = (val >= v ? val / v : 1ll);
			yes |= (b >> i) & 1;
			ans += ok * cost;
			if(yes && !ok) best = min(best, ans + cost);
		}
		return min(ans, best);
	}
	void solve() { 
		int ans = INF;
		rep(i, 0, lg) {
			int L = -INF, R = INF, v = (1ll << i) - 1, bad = 0;
			rep(j, 1, n) {
				int to = a[j] - b[j] * (1ll << i);
				bad |= (to > v);
				L = max(L, to - v);
				R = min(R, to);
			}
			if(L > R || bad) continue;
			if(i == 0) ans = min(ans, max(0ll, -R));
			else ans = min(ans, i + best(L, R, i));
		}
		cout << (ans == INF ? -1 : ans) << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	solve();
	return 0;
}

