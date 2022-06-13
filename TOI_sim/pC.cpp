#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
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
	int n, tot;
	pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	vector<pii> a;
	vector<int> pre;
	void init_(int _n) {
		n = _n, tot = 0;
		a.assign(n, {0, 0});
		pre.assign(2 * n, 0);
	}
	int calculate(int cur) {
		int L = cur + 1, R = cur + n - 1;
		auto diff = [&](int x, int y) {
			int area = (pre[y] - pre[x]) + cross(a[y], a[x]);
			return tot - 2 * area;
		};
		while(R - L > 1) {
			int mid = (L + R) / 2;
			if(diff(cur, mid) >= 0) L = mid;
			else R = mid;
		}
		return min(diff(cur, L), -diff(cur, R));
	} 
	void solve() {
		rrep(i, 0, n - 1) a[i] = a[i] - a[0];
		sort(a.begin() + 1, a.end(), [](pii a, pii b) {
			int foo1 = (a.y == 0 ? a.x > 0 : a.y > 0);
			int foo2 = (b.y == 0 ? a.x > 0 : a.y > 0);
			if(foo1 != foo2) return foo1 > foo2;
			else return cross(a, b) > 0;
		});
		rep(i, 0, n - 1) a.push_back(a[i]);
		rep(i, 1, 2 * n - 1) {
			int cur = cross(a[i - 1], a[i]);
			if(i < n) tot += cur;
			pre[i] = pre[i - 1] + cur;
		}
		print(tot);
		int ans = INF;
		rep(i, 0, n - 1) ans = min(ans, calculate(i));
		cout << ans << "\n";
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) cin >> a[i].x >> a[i].y;
	solve();
	return 0;
}


