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
	int n;
	struct pt { int x, y, w; }; 
	pt operator+(pt a, pt b) { return {a.x + b.x, a.y + b.y, 0ll}; }
	pt operator-(pt a, pt b) { return {a.x - b.x, a.y - b.y, 0ll}; }
	int cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
	int dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
	vector<pt> a;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0, 0});
	}
	void solve() {
		rep(i, 0, n - 1) {
			if((a[i].y == 0 && a[i].x < 0) 
				|| a[i].y < 0) a[i].x *= -1, a[i].y *= -1;
		}
		sort(all(a), [&](pt a, pt b) {
			int foo1 = (a.y == 0 ? a.x > 0 : a.y > 0);
			int foo2 = (b.y == 0 ? b.x > 0 : b.y > 0);
			if(foo1 != foo2) return foo1 > foo2;
			else return cross(a, b) > 0;
		});
		vector<int> v(1, 0);
		pt cur = {0, 0, 0};
		for(auto i : a) {
			if(v.size() > 1 && (cross(cur, i) == 0)) 
				v[v.size() - 1] += i.w;
			else v.push_back(i.w), cur = i;
		}
		int m = v.size() - 1, ans = 0;
		rep(i, 1, m) v.push_back(v[i]);
		rep(i, 1, 2 * m) v[i] += v[i - 1];
		vector<pii> st(2 * m + 1, {0, 0});
		int l = 0, r = 0;
		rep(i, 1, 2 * m) {
			while(st[l].x < i - m) l++;
			ans = max(ans, v[i] - st[l].y);
			pii p = {i, v[i]};
			while(l <= r && st[r].y >= p.y) r --;
			st[++r] = p;
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) cin >> a[i].x >> a[i].y >> a[i].w;
	solve();
	return 0;
}

