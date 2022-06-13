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
	int n;
	vector<int> a;
	struct node {
		int st, ed, ans, len, yes;
	};
	vector<node> v;
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	node pull(node l, node r) {
		if(!l.yes) return r;
		if(!r.yes) return l;
		int dif = max(0ll, l.ed - r.st);
		return {
			l.st, dif + r.ed, 
			l.ans + r.ans + dif * r.len,
			l.len + r.len, 1
		};
	}
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		v.assign(2 * n + 1, {0, 0, 0, 0, 0});
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = {a[L], a[L], 0, 1, 1};
		else {
			build(L, mid), build(mid + 1, R);
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
	int n, q;
	cin >> n >> q;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	build(1, n);
	rep(i, 1, q) {
		int l, r;
		cin >> l >> r;
		cout << query(1, n, l, r).ans << "\n";
	}
	return 0;
}


