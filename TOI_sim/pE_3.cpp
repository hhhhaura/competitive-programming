#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n;
	const int P = 10;
	struct node { int cnt, tag, len, yes; };
	vector<node> v[P];
	vector<int> a;
	void init_(int _n) {
		n = _n;
		rep(i, 0, P - 1) v[i].assign(2 * n + 1, {0, 0, 0, 0});
		a.assign(n + 1, 0);
	}
	int get(int L, int R) {
		return (L + R) | (L != R); 
	}
	node pull(node l, node r) {
		if(!l.yes) return r;
		if(!r.yes) return l;
		return {
			l.cnt + r.cnt,
			0, l.len + r.len, 1
		};
	}
	void push(node &cur, node &l, node &r) {
		if(cur.tag) {
			l.cnt = l.len - l.cnt;
			l.tag ^= 1;

			r.cnt = r.len - r.cnt;
			r.tag ^= 1;
			cur.tag = 0;
		}	
	}
	void build(int L, int R, int id) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[id][nd] = {(a[L] >> id) & 1, 0, 1, 1};
		else {
			build(L, mid, id);
			build(mid + 1, R, id);
			v[id][nd] = pull(v[id][get(L, mid)], v[id][get(mid + 1, R)]);
		}
	}
	node query(int L, int R, int l, int r, int id) {
		int mid = (L + R) / 2, nd = get(L, R);
		int ll = get(L, mid), rr = get(mid + 1, R);
		if(l > R || r < L) return {0, 0, 0, 0};
		if(L != R) push(v[id][nd], v[id][ll], v[id][rr]);
		if(l <= L && r >= R) return v[id][nd];
		else return pull(query(L, mid, l, r, id), 
			query(mid + 1, R, l, r, id));
	}
	void modify(int L, int R, int l, int r, int id) {
		int mid = (L + R) / 2, nd = get(L, R);
		int ll = get(L, mid), rr = get(mid + 1, R);
		if(l > R || r < L) return;
		if(L != R) push(v[id][nd], v[id][ll], v[id][rr]);
		if(l <= L && r >= R) {
			v[id][nd].tag ^= 1;
			v[id][nd].cnt = v[id][nd].len - v[id][nd].cnt;
		}
		else {
			modify(L, mid, l, r, id);
			modify(mid + 1, R, l, r, id);
			v[id][nd] = pull(v[id][ll], v[id][rr]);
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 0, P - 1) build(1, n, i);
	while(q--) {
		int tp, L, R;
		cin >> tp >> L >> R;
		if(tp == 1) {
			int ans = 0;
			rep(j, 0, P - 1) {
				node cur = query(1, n, L, R, j);
				ans |= cur.cnt & 1;
			}
			cout << (ans ? 1 : -1) << "\n";
		}
		else {
			int ll = 0, rr = 0;
			int x; cin >> x;
			rep(j, 0, P - 1) if((x >> j) & 1){
				node pre = query(1, n, L, R, j);
				ll -= pre.cnt * (1 << j);
			}
			rep(j, 0, P - 1) if((x >> j) & 1){
				modify(1, n, L, R, j);
				ll += query(1, n, L, R, j).cnt * (1 << j);
			}
			cout << ll << "\n";
		}
	}
	return 0;
}


