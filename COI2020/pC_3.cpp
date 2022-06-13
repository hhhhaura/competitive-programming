#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
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
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout(){cerr<< endl;}
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define mat vector<vector<int>>
namespace solver2 {
	int n, k, x;
	const int P = 5;
	const int tot = 10;
	vector<int> to;
	vector<int> v = { 10, 8, 18, 28, 9, 21, 6, 24, 23, 29 };
	mat make_mat(int x) { return vector<vector<int>>(x, vector<int>(x, 0)); }
	void init_(int _n, int _k, int _x) {
		n = _n, k = _k, x = _x;
		to.assign(tot, 0);
		rep(i, 0, tot - 1) to[i] = v[i];
	}
	mat mul(mat a, mat b, int sz) {
		mat ans = make_mat(sz);
		rep(i, 0, sz - 1) rep(j, 0, sz - 1) {
			rep(k, 0, sz - 1) ans[i][j] += a[i][k] * b[k][j] % MOD;
			ans[i][j] %= MOD;
		}
		return ans;
	}
	mat pow_(mat a, int times, int sz) {
		mat ans = make_mat(sz);
		rep(i, 0, sz - 1) ans[i][i] = 1;
		for(; times > 0; times >>= 1, a = mul(a, a, sz)) {
			if(times & 1) ans = mul(a, ans, sz);
		}
		return ans;
	}
	void solve() {
		mat a = make_mat(tot);
		rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
			if(__builtin_popcount(to[i] ^ to[j]) == 1) a[i][j] = 1;
		}
		mat s = make_mat(P + 1);
		rep(i, 0, P) {
			if(i - 1 >= 0) s[i - 1][i] += i;
			if(i + 1 <= P) s[i + 1][i] += P - i;
		}
		mat tp = pow_(s, k, P + 1);
		mat b = make_mat(tot);
		rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
			int val = __builtin_popcount(to[i] ^ to[j]);
			b[i][j] = tp[0][val];
		}
		mat c = pow_(b, n / k, tot);
		if(n % k) {
			tp = pow_(s, n % k, P + 1);
			mat d = make_mat(tot);
			rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
				int val = __builtin_popcount(i ^ j);
				d[i][j] = tp[0][val];
			}
			c = d;
		}
		rep(i, 0, tot - 1) cout << c[i][x] << "\n"; 
	}
};
using namespace solver2;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int m, n, k, x;
	cin >> m >> n >> k >> x;
	init_(n, k, x);
	solve();
	return 0;
}



