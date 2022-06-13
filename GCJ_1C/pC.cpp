#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, K;
	vector<int> fac, inv;
	vector<vector<int>> cur, nxt;
	int pow_(int a, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void init_(int _n, int _k) {
		n = _n, K = _k;
		fac.assign(n * n + 1, 1);
		inv.assign(n * n + 1, 1);
		rep(i, 1, n * n) fac[i] = fac[i - 1] * i % MOD;
		inv[n * n] = pow_(fac[n * n], MOD - 2);
		rrep(i, 1, n * n - 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
	}
	int C(int n, int m) {
		if(n < m) return 0;
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	}
	int solve() {
		cur.assign(n + 1, vector<int>(n + 1, 0));
		cur[0][0] = 1;
		int tot = n * (n - 1) / 2;
		rep(i, 1, tot) {
			nxt.assign(n + 1, vector<int>(n + 1, 0));
			rep(j, 2, n) rep(k, 1, n) {
				nxt[j][k] += cur[j][k] * max(0ll, C(j, 2) - i + 1) % MOD;
				nxt[j][k] += C(n - j + 2 , 2) * cur[j - 2][k - 1] % MOD;
				nxt[j][k] += (n - j + 1) * (j - 1) % MOD * cur[j - 1][k] % MOD;
				nxt[j][k] %= MOD;
			} 
			cur = nxt;
		}
		int ans = cur[n][K] * inv[tot] % MOD;
		return (ans + MOD) % MOD;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, k;
		cin >> n >> k;
		init_(n, k);
		cout << "Case #" << tt<< ": " << solve() << "\n";
	}
	return 0;
}

