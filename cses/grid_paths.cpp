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
	int n, m;
	vector<pii> v;
	vector<int> dp, fac, inv;
	int pow_(int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void init_(int _n, int _m) {
		n = _n, m = _m;
		v.assign(m + 1, {0, 0});
		dp.assign(m + 1, 0);
		fac.assign(2 * n + 1, 1);
		inv.assign(2 * n + 1, 1);
		rep(i, 1, 2 * n) fac[i] = fac[i - 1] * i % MOD;
		inv[2 * n] = pow_(fac[2 * n], MOD - 2);
		rrep(i, 1, 2 * n - 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
	}
	int C(int n, int m) {
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	}
	void solve() {
		sort(all(v), [](pii a, pii b) {
			return (a.x + a.y) < (b.x + b.y);
		});
		rep(i, 1, m) {
			int cur = C(v[i].x + v[i].y - 2, v[i].x - 1);
			rep(j, 1, i - 1) if(v[j].x <= v[i].x && v[j].y <= v[i].y) {
				int x = v[i].x - v[j].x, y = v[i].y - v[j].y;
				cur -= dp[j] * C(x + y, x) % MOD;
				cur %= MOD;
			}
			dp[i] = (cur + MOD) % MOD;
		}
		int ans = C(2 * n - 2, n - 1);
		rep(i, 1, m) {
			int x = n - v[i].x, y = n - v[i].y;
			ans -= C(x + y, x) * dp[i] % MOD;
			ans %= MOD;
		}
		cout << (ans + MOD) % MOD << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 1, m) cin >> v[i].x >> v[i].y;
	solve();
	return 0;
}


