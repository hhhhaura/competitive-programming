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
#define x first
#define y second
namespace solver {
	const int p = 1000000;
	const int P = 2000000;
	vector<pair<int, pii>> op;
	vector<int> v;
	void init_() {
		op.clear();
		v.assign(2 * P + 1, 0);
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		v[nd] = v[get(L, mid)] + v[get(mid + 1, R)];
	}
	void modify(int L, int R, int id, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] += val;
		else {
			if(id <= mid) modify(L, mid, id, val);
			else modify(mid + 1, R, id, val);
			pull(L, R);
		}
	}
	int query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		else if(l <= L && r >= R) return v[nd];
		else return query(L, mid, l, r) + query(mid + 1, R, l, r);
	}
	void solve() {
		sort(all(op));
		int ans = 0;
		for(auto i : op) {
			if(abs(i.y.x) == INF) {
				if(i.y.x < 0) modify(0, P, i.y.y, -1);
				else modify(0, P, i.y.y, 1);
			}
			else ans += query(0, P, i.y.x, i.y.y);
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_();
	rep(i, 1, n) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		b += p, d += p;
		if(a == c) op.push_back({a, {b, d}});
		else {
			assert(b == d);
			op.push_back({a, {INF, b}});
			op.push_back({c, {-INF, b}});
		}
	}
	solve();
	return 0;
}


