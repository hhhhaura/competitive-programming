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
	const int P = 2000000;
	auto pow_ = [](int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	vector<int> fac(P + 1, 1), inv(P + 1, 1);
	rep(i, 1, P) fac[i] = fac[i - 1] * i % MOD;
	inv[P] = pow_(fac[P], MOD - 2);
	rrep(i, 0, P - 1) inv[i] = (i + 1) * inv[i + 1] % MOD;
	auto C = [&](int a, int b) {
		int ans = fac[a] * inv[b] % MOD * inv[a - b] % MOD;
		return ans;
	};
	int n; cin >> n;
	string s; cin >> s;
	int a = 0, b = 0, ans = 0, cur = 0;
	for(auto i : s) {
		cur += (i == '(' ? 1 : -1);
		a += (i == '(');
		b += (i == ')');
		if(cur < 0 || n & 1 || a > n / 2) {
			cout << "0\n";
			return 0;
		} 
	}
	if(a == n / 2) {
		cout << "1\n";
		return 0;
	}
	n /= 2;
	ans = C(n - a + n - b, n - a);
	int x = b - 1, y = a + 1;
	print(a, b, x, y);
	ans -= C(n - x + n - y, n - y);
	ans = (ans % MOD + MOD) % MOD;
	cout << ans << "\n";
	return 0;
}




