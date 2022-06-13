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
struct BIT {
	int n;
	vector<int> v;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & -x;
	}
	void modify(int x, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			v[i] += val;
		}
	}
	int query(int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += v[i];
		}
		return ans;
	}
};
namespace solver {
	int n;
	vector<int> a, st, ed;
	BIT x, y;
	void init_(int _n) {
		n = _n;
		a.assign(2 * n + 1, 0);
		st.assign(2 * n + 1, 2 * n);
		ed.assign(2 * n + 1, 0);
		x.init_(2 * n + 1);
		y.init_(2 * n + 1);
	}
	void modify(int L, int R, int val) {
		L++, R++;
		x.modify(L, val);
		x.modify(R + 1, -val);
		y.modify(L, L * val);
		y.modify(R + 1, -val * (R + 1));
	}
	int query(int L, int R) {
		L++, R++;
		int aa = x.query(R) * (R + 1) - y.query(R);
		int bb = x.query(L - 1) * (L) - y.query(L - 1);
		return aa - bb;
	}
	void solve() {
		int r = 0;
		vector<int> cnt(n + 1, 0);	
		rep(i, 1, 2 * n) {
			while(r < 2 * n && !cnt[a[r + 1]]
				&& (r - i + 2) * 2 < n) r ++, cnt[a[r]] ++;
			st[i - 1] = r;
			cnt[a[i]] --;
		}
		cnt.assign(n + 1, 0);
		int l = 2 * n + 1;
		rrep(i, 1, 2 * n) {
			while(l > 1 && !cnt[a[l - 1]]
				&& (i - l + 2) * 2 < n) l--, cnt[a[l]] ++;
			ed[i] = l - 1;
			cnt[a[i]] --;
		}
		int ans = 0, c = -1;
		rep(i, 0, n - 1) {
			modify(i + 1, st[i], -1);
			while(c + 1 < 2 * n && c + 1 <= st[i]) {
				c++, modify(c + 1, st[c], 1);
			}
			ans += query(ed[i + n], i + n - 1);
		}
		cout << ans / 3 << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	solve();
	return 0;
}




