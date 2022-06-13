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
struct BIT {
	int n, ops;
	vector<int> v;
	vector<pii> st;
	void init_(int _n) {
		n = _n, ops = 0;
		st.clear();
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & (-x);
	}
	void modify(int x, int val, int tp) {
		if(tp == 1) st.push_back({x, val}), ops ++;
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
	void undo() {
		ops--;
		pii p = st.back();
		st.pop_back();
		modify(p.first, -p.second, 0);
	}
};
namespace solver {
	int n;
	vector<int> a, mx, pre, suf, to, tot;
	vector<vector<int>> v;
	BIT bit;
	void init_(int _n) {
		n = _n, bit.init_(n);
		tot.clear();
		a.assign(n + 1, 0);
		mx.assign(n + 2, 0);
		pre.assign(n + 2, 0);
		suf.assign(n + 2, 0);
		to.assign(n + 2, 0);
		v.assign(n + 2, vector<int>());
	}
	void solve() {
		sort(all(tot));
		tot.resize(unique(all(tot)) - tot.begin());
		rep(i, 1, n) a[i] = lower_bound(all(tot), a[i]) - tot.begin() + 1;
		rrep(i, 1, n) mx[i] = max(mx[i + 1], a[i]);
		rep(i, 1, n) {
			pre[i] = bit.query(a[i] - 1) + 1;
			bit.modify(a[i], pre[i], 1);
		}
		while(bit.ops) bit.undo();
		rrep(i, 1, n) {
			suf[i] = bit.query(n) - bit.query(a[i]) + 1;
			suf[i] = (suf[i] + MOD) % MOD;
			bit.modify(a[i], suf[i], 1);
		}
		while(bit.ops) bit.undo();
		rrep(i, 1, n) {
			int L = i, R = n + 1;
			while(R - L > 1) {
				int mid = (L + R) / 2;
				if(mx[mid] <= a[i]) R = mid;
				else L = mid;
			}
			if(L != i) v[L].push_back(i);
		}
		rep(i, 1, n) {
			bit.modify(a[i], 1, 1);
			to[i] = 1;
			for(auto j : v[i]) {
				to[j] = bit.query(n) - bit.query(a[j]);
				to[j] = (to[j] + MOD) % MOD;
				bit.modify(a[j], to[j], 1);
			}
			while(bit.ops) bit.undo();
		}
		int ans = 0;
		rep(i, 1, n) {
			int cur = pre[i] * (suf[i] - to[i]) % MOD;
			cur = (cur % MOD + MOD) % MOD;
			//print(i, cur, suf[i], to[i], pre[i]);
			ans = (ans + cur) % MOD;
		}
		cout << (ans + MOD) % MOD << "\n";
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) {
			cin >> a[i];
			tot.push_back(a[i]);
		}
		solve();
	}
	return 0;
}


