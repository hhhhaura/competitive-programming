#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__, kout("["+string(#a)+"] = ", a)
void kout() { cerr << endl; }
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	const int P = 10000000;
	struct node { int mx, tag, l, r; };
	vector<node> v(P, {0, 0, 0, 0});
	int n, k, ii;
	vector<pair<int, pii>> a;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		ii = 1;
		a.clear();
	}
	void modify(int nd, int L, int R, int l, int r, int val) {
		if(l > R || r < L) return;
		else if(l <= L && r >= R) {
			v[nd].tag += val, v[nd].mx += val;
		}
		else {
			int mid = (L + R) / 2;
			if(!v[nd].l) v[nd].l = ++ii;
			if(!v[nd].r) v[nd].r = ++ii;
			modify(v[nd].l, L, mid, l, r, val);
			modify(v[nd].r, mid + 1, R, l, r, val);
			int ll = v[nd].l, rr = v[nd].r;
			v[nd].mx = max(v[ll].mx, v[rr].mx) + v[nd].tag;
		}
	}
	void solve() {
		sort(all(a));
		int cur = -INF, L = 0, R = 4e9, det = 2e9;
		int ans = 0;
		for(auto i : a) {
			pii op = i.second;
			if(i.first != cur) {
				cur = i.first;
				ans = max(ans, v[1].mx);
			}
			modify(1, L, R, max(L, op.first - 2ll * k + det), 
				op.first + det, op.second);
		}
		cout << max(ans, v[1].mx)  << "\n";
	}
}
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) {
		int x, y;
		cin >> x >> y;
		int l = x - y, r = x + y;
		a.push_back({l, {r, 1}});
		a.push_back({l + 2ll * k + 1, {r, -1}});
	}
	solve();
	return 0;
}


