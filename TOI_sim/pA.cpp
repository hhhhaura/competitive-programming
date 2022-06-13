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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	const int P = 2000000;
	vector<int> fac(P + 1, 1), inv(P + 1, 1);
	auto pow_ = [](int a, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	rep(i, 1, P) fac[i] = fac[i - 1] * i % MOD;
	inv[P] = pow_(fac[P], MOD - 2);
	rrep(i, 1, P - 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
	int n, m;
	cin >> n >> m;
	auto C = [&](int n, int m) {
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	};
	int ans = C(n + m, 1) * C(n + m - 1, n - 1) % MOD;
	ans = (ans + C(n + m, 1) * C(n + m - 1, m - 1) % MOD) % MOD;
	cout << ans << "\n";
	return 0;
}


