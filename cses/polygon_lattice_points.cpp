//Pick's Theorum
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
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	vector<pii> a;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
	}
	void solve() {
		int ans = 0, cnt = 0;
		rep(i, 0, n - 1) {
			int to = (i + 1) % n;
			pii vec = a[i] - a[to];
			ans += cross(a[i], a[to]);
			cnt += abs(__gcd(vec.x, vec.y));
		}
		ans = abs(ans);
		cout << (ans - cnt + 2) / 2 << " ";
		cout << cnt << "\n";

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


