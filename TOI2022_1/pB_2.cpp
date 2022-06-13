#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000ll
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
struct seg_tree {
	int n;
	vector<int> v;
	void init_(int _n) {
		n = _n;
		v.assign(2 * n + 1, 0);
		rep(i, 1, n) v[get(i, i)] = INF;
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int l = get(L, mid), r = get(mid + 1, R);
		v[l] = min(INF, v[nd] + v[l]);
		v[r] = min(INF, v[nd] + v[r]);
		v[nd] = 0;
	}
	int query(int L, int R, int id) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) return v[nd];
		else {
			push(L, R);
			if(id <= mid) return query(L, mid, id);
			else return query(mid + 1, R, id);
		}
	}
	void modify1(int L, int R, int id, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = val;
		else {
			push(L, R);
			if(id <= mid) modify1(L, mid, id, val);
			else modify1(mid + 1, R, id, val);
		}
	}
	void modify2(int L, int R, int l, int r, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) v[nd] += val;
		else {
			modify2(L, mid, l, r, val);
			modify2(mid + 1, R, l, r, val);
		}
	}
};
namespace solver {
	int n;
	vector<vector<pii>> A, B, v;
	map<pii, int> a, b;
	seg_tree dpa, dpb;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, vector<pii>());
		A.assign(n + 1, vector<pii>());
		B.assign(n + 1, vector<pii>());
		a.clear();
		b.clear();
		dpa.init_(n);
		dpb.init_(n);
	}
	void solve() {
		dpa.modify1(1, n, 1, 0);
		dpb.modify1(1, n, 1, 0);
		int va = INF, vb = INF, ans = INF;
		rep(i, 2, n) {
			if(a.find({i - 1, i}) != a.end()) {
				dpa.modify2(1, n, 1, i - 1, a[pii(i - 1, i)]);
			}
			else dpa.modify2(1, n, 1, i - 1, INF);
			if(b.find({i - 1, i}) != b.end()) {
				dpb.modify2(1, n, 1, i - 1, b[pii(i - 1, i)]);
			}
			else dpb.modify2(1, n, 1, i - 1, INF);
			int val = dpa.query(1, n, i - 1);
			dpa.modify1(1, n, i - 1, min(va, val));
			val = dpb.query(1, n, i - 1);
			dpb.modify1(1, n, i - 1, min(vb, val));
			va = INF, vb = INF;
			if(i != n) {
				for(auto j : A[i + 1]) {
					int val = dpb.query(1, n, j.x);
					va = min(va, val + j.y);
				}
				for(auto j : B[i + 1]) {
					int val = dpa.query(1, n, j.x);
					vb = min(vb, val + j.y);
				}
			}
			if(i == n) for(auto j : v[i]) {
				int val = 0;
				if(j.x > 0) val = dpb.query(1, n, j.x) + j.y;
				else val = dpa.query(1, n, -j.x) + j.y;
				ans = min(ans, val);
			}
		}
		cout << (ans == INF ? -1 : ans)  << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int x, y, c;
		cin >> x >> y >> c;
		if(x < 0) {
			pii p = {-y, -x};
			if(b.find(p) == b.end()) b[p] = c;
			else b[p] = min(b[p], c);
			B[-x].push_back({-y, c});
		}
		else if(y > 0) {
			pii p = {x, y};
			if(a.find(p) == a.end()) a[p] = c;
			else a[p] = min(a[p], c);
			A[y].push_back({x, c});
		}
		else {
			if(abs(x) > abs(y)) swap(x, y);
			v[abs(y)].push_back({x, c});
		}
	}
	solve();
	return 0;
}






