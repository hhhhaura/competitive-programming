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
#define mat vector<vector<int>>
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	mat seed = {
		{1, 1},
		{1, 0}
	};
	auto mul = [&](mat a, mat b) {
		mat ans = { {0, 0}, {0, 0} };
		rep(i, 0, 1) rep(j, 0, 1) {
			rep(k, 0, 1) ans[i][j] += a[i][k] * b[k][j] % MOD;;
			ans[i][j] %= MOD;
		}
		return ans;
	};
	auto pow_ = [&](mat a, int times) {
		mat ans = { {1, 0}, {0, 1} };
		for(; times > 0; times >>= 1, a = mul(a, a)) {
			if(times & 1) ans = mul(ans, a);
		}
		return ans;
	};
	int n; cin >> n;
	mat to = pow_(seed, n - 1);
	if(n == 0) cout << "0\n";
	else cout << to[0][0] << "\n";
	return 0;
}


