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
	vector<int> a, b, v;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & (-x);
	}
	void modify(int x, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			v[i] = (v[i] + val) % MOD;
		}
	}
	int query(int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans = (ans + v[i]) % MOD;
		}
		return ans;
	}
	void solve() {
		sort(all(b));
		b.resize(unique(all(b)) - b.begin());
		rep(i, 1, n) {
			int id = lower_bound(all(b), a[i]) - b.begin() + 1;
			a[i] = id;
		}
		int ans = 0;
		rep(i, 1, n) {
			int cur = query(a[i] - 1) + 1;
			ans = (ans + cur) % MOD;
			modify(a[i], cur);
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
		cin >> a[i];
		b.push_back(a[i]);
	}
	solve();
	return 0;
}


