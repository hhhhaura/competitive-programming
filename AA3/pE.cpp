#define wiwihorz
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld double
#define pii pair<int, int>
#define ramdon mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-12)

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<__LINE__<<": ",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " ", ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ...e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, d;
	pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int sign(lld x) { return abs(x) < eps ? 0 : (x > 0 ? 1 : -1); }
	lld len(pii a) { return sqrt(dot(a, a)); }
	vector<pii> a;
	void init_(int _n, int _d) {
		n = _n, d = 2ll * _d;
		a.assign(n, {0, 0});
	}
	int solve() {
		vector<pair<lld, int>> v;
		int cnt = 1, ans = 1;
		const lld PI = acos(-1);
		rep(i, 1, n - 1) {
			pii p = a[i] - a[0];
			lld ang = atan2(p.y, p.x);
			v.push_back({ang, 1});
			v.push_back({ang + PI + eps, -1});
			if(sign(len(p) - d) > 0) {
				lld det = asin(d / len(p));
				v.push_back({ang + det + eps, -1});
				v.push_back({ang - det + PI, +1});
			}
		}
		int m = v.size();
		rep(i, 0, m - 1) v.push_back({v[i].x + 2 * PI, v[i].y});
		sort(all(v));
		for(auto i : v) {
			cnt += i.y;
			ans = max(ans, cnt);
		}
		return ans;
	
	}
}
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, d; 
	cin >> n >> d;
	init_(n, d);
	rep(i, 0, n - 1) 
		cin >> a[i].x >> a[i].y;
	int ans = 0;
	rep(i, 0, n - 1) {
		if(i) swap(a[i], a[0]);
		ans = max(ans, solve());
		if(i) swap(a[i], a[0]);
	}
	cout << ans << "\n";
	return 0;
}


