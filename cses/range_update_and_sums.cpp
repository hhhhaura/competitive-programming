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
namespace seg {
	int n; // 維護的資料是好的
	vector<int> add, chg, mx, sum, a;
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int l = get(L, mid), r = get(mid + 1, R);
		int len = R - L + 1;
		mx[nd] = (chg[nd] ? chg[nd] : max(mx[l], mx[r])) + add[nd];
		sum[nd] = (chg[nd] ? chg[nd] * len : sum[l] + sum[r]) + add[nd] * len;
	} 
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int l = get(L, mid), r = get(mid + 1, R);
		if(chg[nd]) {
			add[l] = add[r] = 0;
			chg[l] = chg[r] = chg[nd];
			mx[l] = mx[r] = chg[nd];
			sum[l] = chg[nd] * (mid - L + 1);
			sum[r] = chg[nd] * (R - mid);
			chg[nd] = 0;
		}
		if(add[nd]) {
			add[l] += add[nd], add[r] += add[nd];
			mx[l] += add[nd], mx[r] += add[nd];
			sum[l] += add[nd] * (mid - L + 1);
			sum[r] += add[nd] * (R - mid);
			add[nd] = 0;
		}
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) mx[nd] = sum[nd] = a[L];
		else {
			build(L, mid);
			build(mid + 1, R);
			pull(L, R);
		}
	}
	void init_(int _n, vector<int> _a) {
		n = _n, a = _a;
		add.assign(2 * n + 1, 0);
		chg.assign(2 * n + 1, 0);
		sum.assign(2 * n + 1, 0);
		mx.assign(2 * n + 1, 0);
		build(1, n);
	}
	void modify(int L, int R, int l, int r, int tp, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(L != R) push(L, R);
		if(l <= L && r >= R) {
			if(tp == 1) {
				chg[nd] = val, mx[nd] = val;
				add[nd] = 0, sum[nd] = (R - L + 1) * val;
			}
			else {
				add[nd] += val, mx[nd] += val;
				sum[nd] += (R - L + 1) * val;
			}
		}
		else {
			modify(L, mid, l, r, tp, val);
			modify(mid + 1, R, l, r, tp, val);
			pull(L, R);
		}
	}
	int query_max(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		if(L != R) push(L, R);
		if(l <= L && r >= R) return mx[nd];
		else {
			int val = max(query_max(L, mid, l, r), query_max(mid + 1, R, l, r));
			return (chg[nd] ? chg[nd] : val) + add[nd];
		}
	}
	int query_sum(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		if(L != R) push(L, R);
		if(l <= L && r >= R) return sum[nd];
		else {
			int val = query_sum(L, mid, l, r) + query_sum(mid + 1, R, l, r);
			int len = min(R, r) - max(l, L) + 1;
			return (chg[nd] ? chg[nd] * len : val) + add[nd] * len;
		}
	}
};

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	seg::init_(n, a);
	rep(i, 1, q) {
		int tp, l, r;
		cin >> tp >> l >> r;
		if(tp == 1 || tp == 2) {
			int x; cin >> x;
			seg::modify(1, n, l, r, 3 - tp, x);
		}
		else if(tp == 3) cout << seg::query_sum(1, n, l, r) << "\n";
		else cout << seg::query_max(1, n, l, r) << "\n";
	}
	return 0;
}



