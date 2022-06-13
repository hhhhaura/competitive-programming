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
#define x first
#define y second
namespace solver {
	int n;
	pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int sign(int x) { return (x == 0 ? 0 : (x > 0 ? 1 : -1)); }
	lld abss(pii a) { return sqrt(a.x * a.x + a.y * a.y); } 
	vector<pii> a, b;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
	}
	int check(pii a, pii b, pii o) {
		return sign(cross(a - o, b - o)) < 0;
	}
	int dis(pii a, pii b, pii c) {
		return abs(cross(b - a, c - a));
	}
	void solve() {
		sort(all(a));
		int sz = 0, h;
		for(auto i : a) {
			while(sz > 1 && !check(b[sz - 2], b[sz - 1], i)) 
				sz --, b.pop_back();
			sz++, b.push_back(i);
		}
		b.pop_back(), sz--;
		reverse(all(a)), h = sz;
		for(auto i : a) {
			while(sz - h > 1 && !check(b[sz - 2], b[sz - 1], i))
				sz --, b.pop_back();
			sz++, b.push_back(i);
		}
		b.pop_back(), sz--;
		int r = 1; lld ans = INF;
		cout << fixed << setprecision(12);
		if(sz == 2) {
			cout << 0.0 << "\n";
			return;
		}
		rep(i, 0, sz - 1) {
			int j = (i + 1 == sz? 0 : i + 1);
			while(dis(b[i], b[j], b[(r + 1) % sz]) >
				dis(b[i], b[j], b[r])) r = (r + 1) % sz;
			int cur = dis(b[i], b[j], b[r]);
			ans = min(ans, cur / abss(b[i] - b[j]));
		}
		cout << ans / 2 << "\n";

	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	for(auto &i : a) cin >> i.x >> i.y;
	solve();
	return 0;
}

