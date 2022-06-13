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
		{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 1, 0}
	};
	mat id = {
		{1, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1}
	};
	auto mul = [&](mat a, mat b) {
		mat ans = mat(6, vector<int>(6, 0));
		rep(i, 0, 5) rep(j, 0, 5) {
			rep(k, 0, 5) {
				ans[i][j] += a[i][k] * b[k][j] % MOD;
				if(ans[i][j] > MOD) ans[i][j] -= MOD;
			}
		}
		return ans;
	};
	auto pow_ = [&](mat a, int times) {
		mat ans = id;
		for(; times > 0; times >>= 1, a = mul(a, a)) {
			if(times & 1) ans = mul(ans, a);
		}
		return ans;
	};
	int n; cin >> n;
	vector<int> v = {16, 8, 4, 2, 1, 1};
	if(n < 6) cout << v[5 -n] << "\n";
	else {
		mat to = pow_(seed, n - 5);
		int ans = 0;
		rep(i, 0, 5) ans = (ans + v[i] * to[0][i] % MOD) % MOD;
		cout << ans << "\n";
	}
	return 0;
}


