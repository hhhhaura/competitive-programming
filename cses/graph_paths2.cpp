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
#define INF 4000000000000000000
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
	int n, m, k;
	cin >> n >> m >> k;
	mat mp, id;
	mp.assign(n, vector<int>(n, INF));
	id.assign(n, vector<int>(n, INF));
	rep(i, 0, n - 1) id[i][i] = 0;
	rep(i, 1, m) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		mp[a][b] = min(mp[a][b], c);
	}
	auto mul = [&](mat a, mat b) {
		mat ans = mat(n, vector<int>(n, INF));
		rep(i, 0, n - 1) rep(j, 0, n - 1) {
			rep(k, 0, n - 1) ans[i][j] = min(ans[i][j], a[i][k] + b[k][j]);
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
	mat to = pow_(mp, k);
	cout << (to[0][n - 1] == INF ? -1 : to[0][n - 1])  << "\n";

	return 0;
}



