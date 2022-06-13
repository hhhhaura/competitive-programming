#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
struct BIT {
	int n;
	vector<int> v;
	vector<int> ops;
	void init_(int _n) {
		n = _n;
		ops.clear();
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & -x;
	}
	int query(int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += v[i];
		}
		return ans;
	}
	void undo() {
		while(ops.size()) {
			int cur = ops.back();
			ops.pop_back();
			modify(cur, -1, 0);
		}
	}
	void modify(int x, int val, int yes) {
		if(yes) ops.push_back(x);
		for(int i = x; i <= n; i += lowbit(i)) {
			v[i] += val;
		}
	}
};
namespace solver {
	int n, m;
	BIT bit;
	struct pt {int x, y, z; };
	vector<pt> a;
	vector<int> q, L, R, v, t;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		bit.init_(n);
		a.assign(n, {0, 0, 0});
		v.assign(n + 1, 0);
		q.assign(m + 1, 0);
		L.assign(m + 1, 0);
		R.assign(m + 1, 0);
		t.assign(n + 1, INF);
	}
	void CDQ(int L, int R, vector<int> &ans) {
		if(L == R) return;
		int mid = (L + R) / 2;
		CDQ(L, mid, ans);
		CDQ(mid + 1, R, ans);
		int ii = L;
		bit.undo();
		rep(i, mid + 1, R) {
			while(ii <= mid && a[i].y > a[ii].y) {
				bit.modify(a[ii].z, 1, 1), ii++;
			}
			int val = bit.query(n) - bit.query(a[i].z);
			if(a[i].x <= m) ans[a[i].x] += val; 
		}
		vector<pt> tp(R - L + 1, {0, 0, 0});
		merge(a.begin() + L, a.begin() + mid + 1,
			a.begin() + mid + 1, a.begin() + R + 1, tp.begin(),
			[](pt a, pt b) { return a.y < b.y; }
		);
		rep(i, L, R) a[i] = tp[i - L];
		return;
	}
	void solve() {
		rep(i, 0, n - 1) {
			a[i] = {t[v[i + 1]], i + 1, v[i + 1]};
		}
		sort(all(a), [&](pt a, pt b) {
			return a.x > b.x;
		});
		CDQ(0, n - 1, L);
		rep(i, 0, n - 1) swap(a[i].y, a[i].z);
		sort(all(a), [&](pt a, pt b) {
			return a.x > b.x;
		});
		bit.init_(n);
		CDQ(0, n - 1, R);
		int ans = 0;
		bit.init_(n);
		rrep(i, 1, n) {
			ans += bit.query(v[i] - 1);
			bit.modify(v[i], 1, 1);
		}
		cout << ans << "\n";
		rep(i, 1, m - 1) {
			ans -= L[i] + R[i];
			cout << ans << "\n";
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	while(cin >> n >> m) {
		init_(n, m);
		rep(i, 1, n) cin >> v[i];
		rep(i, 1, m) cin >> q[i], t[q[i]] = i;
		solve();
	}
	return 0;
}

