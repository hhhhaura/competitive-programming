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
	int C, mask, n;
	struct node {
		int a, b, c, ans, yes;
	};
	vector<int> a;
	vector<node> v;
	void init_(int _C, int _n) {
		C = _C, n = _n;
		mask = (1ll << C) - 1;
		a.assign(n + 1, 0);
		v.assign(2 * n + 1, {0, 0, 0, 0, 0});
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	node pull(node l, node r) {
		if(!l.yes) return r;
		if(!r.yes) return l;
		int a = ((r.a & r.b) | (~r.b & (l.a ^ r.a))) & mask;
		int b = l.b | r.b, c = (~r.b & l.c) & mask;
		return {a, b, c, (~a ^ ~b ^ c) & mask, 1};
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = {a[L] ,mask & ~a[L], mask & ~a[L], a[L], 1};
		else {
			build(L, mid), build(mid + 1, R);
			v[nd] = pull(v[get(L, mid)], v[get(mid + 1, R)]);
		}
	}
	void modify(int L, int R, int id, int x) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = {x, mask & ~x, mask & ~x, x, 1};
		else {
			if(id <= mid) modify(L, mid, id, x);
			else modify(mid + 1, R, id, x);
			v[nd] = pull(v[get(L, mid)], v[get(mid + 1, R)]);
		}
	}
	node query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return {0, 0, 0, 0, 0};
		else if(l <= L && r >= R) return v[nd];
		else return pull(query(L, mid, l, r), query(mid + 1, R, l, r));
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q, c;
	cin >> n >> q >> c;
	init_(c, n);
	rep(i, 1, n) cin >> a[i];
	build(1, n);
	rep(i, 1, q) {
		int tp, x, y;
		cin >> tp >> x >> y;
		if(tp == 1) cout << query(1, n, x, y).ans << "\n";
		else modify(1, n, x, y);
	}
	return 0;
}

