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
	int n, q, ii, tot;
	const int P = 5000000;
	vector<int> a, arr, cpy;
	vector<int> v(P + 1, 0), l(P + 1, 0), r(P + 1, 0);
	void init_(int _n, int _q) {
		n = _n, q = _q;
		ii = 1, tot = 1;
		a.assign(n + 1, 0);
		arr.assign(q + 1, 0);
		cpy.assign(q + 1, 0);
	}
	void build(int nd, int L, int R) {
		int mid = (L + R) / 2;
		if(L == R) v[nd] = a[L];
		else {
			l[nd] = ++ii, r[nd] = ++ii;
			build(l[nd], L, mid);
			build(r[nd], mid + 1, R);
			v[nd] = v[l[nd]] + v[r[nd]];
		}
	}
	int query(int nd, int L, int R, int ll, int rr) {
		int mid = (L + R) / 2;
		if(ll > R || rr < L || !nd ) return 0;
		else if(ll <= L && rr >= R) return v[nd];
		else return query(l[nd], L, mid, ll, rr) 
			+ query(r[nd], mid + 1, R, ll, rr);
	}
	int copy(int nd) {
		v[++ii] = v[nd];
		l[ii] = l[nd];
		r[ii] = r[nd];
		return ii;
	}
	void modify(int pre, int cur, int L, int R, int id, int val) {
		if(L == R) v[cur] = val;
		else {
			int mid = (L + R) / 2;
			if(id <= mid) {
				if(!l[pre]) l[cur] = ++ii;
				else l[cur] = copy(l[pre]);
				modify(l[pre], l[cur], L, mid, id, val);
			}
			else {
				if(!r[pre]) r[cur] = ++ii;
				else r[cur] = copy(r[pre]);
				modify(r[pre], r[cur], mid + 1, R, id, val);
			}
			v[cur] = v[l[cur]] + v[r[cur]];
		}
	}
	void solve() {
		arr[1] = 1;
		build(1, 1, n);
		rep(i, 1, q) {
			int tp; cin >> tp;
			if(tp == 1) {
				int k, a, x;
				cin >> k >> a >> x;
				int cur = copy(arr[k]);
				modify(arr[k], cur, 1, n, a, x);
				arr[k] = cur;
			}
			else if(tp == 2) {
				int k, a, b;
				cin >> k >> a >> b;
				cout << query(arr[k], 1, n, a, b) << "\n";
			}
			else {
				int k; cin >> k;
				arr[++tot] = copy(arr[k]);
			}
		}
	}

	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n, q);
	rep(i, 1, n) cin >> a[i];
	solve();
	return 0;
}

	
