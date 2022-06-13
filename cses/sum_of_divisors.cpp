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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	const int inv2 = 500000004;
	int ans = 0, k = 1000000;
	rep(i, 1, n) {
		if(n / i <= k) break;
		ans += n / i * i;
		ans %= MOD;
	}
	ans %= MOD;
	rep(i, 1, k) {
		int L = n / (i + 1) + 1, R = n / i;
		int a = (R - L + 1) % MOD, b = (R + L) % MOD;
		if(R >= L) ans += a * b % MOD * inv2 % MOD * i % MOD;
		ans %= MOD;
	}
	cout << ans << "\n";
	return 0;
}


