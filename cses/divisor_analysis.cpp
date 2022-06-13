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
	vector<int> a(n + 1, 0), pow(n + 1, 0);
	vector<int> pre(n + 1, 1), suf(n + 2, 1);
	rep(i, 1, n) cin >> a[i] >> pow[i];
	auto pow_ = [&](int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	auto inv = [&](int a) {
		return pow_(a, MOD - 2);
	};
	rep(i, 1, n) pre[i] = pre[i - 1] * (pow[i] + 1) % (MOD - 1);
	rrep(i, 1, n) suf[i] = suf[i + 1] * (pow[i] + 1) % (MOD - 1);
	int cnt = 1, sum = 1, pro = 1; 
	rep(i, 1, n) {
		int num = a[i], x = pow[i];
		cnt = cnt * (x + 1) % MOD;
		sum = sum * (pow_(num, x + 1) - 1) % MOD * inv(num - 1) % MOD;
		int to = pre[i - 1] * suf[i + 1] % (MOD - 1);
		int seq = (1 + x) * x / 2 % (MOD - 1);
		pro = pro * pow_(num, to * seq % (MOD - 1)) % MOD;
	}
	cout << cnt << " " << sum << " " << pro << "\n";
	return 0;
}


