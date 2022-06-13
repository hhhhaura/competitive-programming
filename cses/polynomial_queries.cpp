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
	int n, m;
	struct node {
		int b, c, tag, l, len, yes;
	};
	vector<int> a, pre;
	vector<node> v;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		v.assign(2 * n + 1, {0, 0, 0, 0, 0, 0});
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	node pull(node l, node r) {
		if(!l.yes) return r;
		if(!r.yes) return l;
		return {
			l.b + r.b, l.c + r.c,
			0, l.l, l.len + r.len, 1
		};
	}
	void push(node &n, node &l, node &r) {
		if(n.tag) {
			int val = n.tag;
			l.b += val * l.len;
			l.c += val * (2ll * l.l + l.len - 1) * l.len / 2;
			l.tag += val;

			r.b += val * r.len;
			r.c += val * (2ll * r.l + r.len - 1) * r.len / 2;
			r.tag += val;

			n.tag = 0;
		}
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = {pre[L], L * pre[L], 0, L, 1, 1};
		else {
			build(L, mid);
			build(mid + 1, R);
			v[nd] = pull(v[get(L, mid)], v[get(mid + 1, R)]);
		}
	}
	void modify(int L, int R, int l, int r, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		int ll = get(L, mid), rr = get(mid + 1, R);
		if(l > R || r < L) return;
		if(L != R) push(v[nd], v[ll], v[rr]);
		if(l <= L && r >= R) {
			v[nd].b += v[nd].len * val;
			v[nd].c += val * (2ll * v[nd].l + v[nd].len - 1) * v[nd].len / 2;
			v[nd].tag += val;
		}
		else {
			modify(L, mid, l, r, val);
			modify(mid + 1, R, l, r,val);
			v[nd] = pull(v[ll], v[rr]);
		}
	}
	node query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		int ll = get(L, mid), rr = get(mid + 1, R);
		if(l > R || r < L) return {0, 0, 0, 0, 0, 0};
		if(L != R) push(v[nd], v[ll], v[rr]);
		if(l <= L && r >= R) return v[nd];
		else return pull(query(L, mid, l, r), query(mid + 1, R, l, r));
	}
	void solve() {
		rep(i, 1, n) pre[i] = a[i] - a[i - 1];
		build(1, n);
		rep(i, 1, m) {
			int tp, a, b;
			cin >> tp >> a >> b;
			if(tp == 1) {
				modify(1, n, a, b, 1);
				if(b != n) modify(1, n, b + 1, b + 1, -(b - a + 1));
			}
			else {
				node R = query(1, n, 1, b);
				node L = query(1, n, 1, a - 1);
				int rval = (b + 1) * R.b - R.c;
				int lval = a * L.b - L.c;
				cout << rval - lval  << "\n";
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


