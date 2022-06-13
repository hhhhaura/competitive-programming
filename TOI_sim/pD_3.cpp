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
#define MOD 998244353
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
#define mat vector<vector<int>>
namespace solver {
	int n, m, l;
	vector<vector<int>> s;
	vector<int> a, f;
	void init_(int _n, int _m, int _l) {
		n = _n, m = _m, l = _l;
		s.assign(n + 2, vector<int>(n + 2, 0));
		a.assign(n + 1, 0);
		f.assign(n + 1, 0);
	}
	mat mul(mat a, mat b) {
		mat ans = vector<vector<int>>(n + 2, vector<int>(n + 2, 0));
		rep(i, 0, n + 1) rep(j, 0, n + 1) {
			rep(k, 0, n + 1) ans[i][j] += a[i][k] * b[k][j] % MOD;
			ans[i][j] %= MOD;
		}
		return ans;
	}
	mat pow_(mat a, int times) {
		mat ans = vector<vector<int>>(n + 2, vector<int>(n + 2, 0));
		rep(i, 0, n + 1) ans[i][i] = 1;
		for(;times > 0; times >>= 1, a = mul(a, a)) {
			if(times & 1) ans = mul(ans, a);
		}
		return ans;
	}
	void solve() {
		rep(i, 2, n) {
			int pre = f[i - 1];
			while(pre && a[pre + 1] != a[i]) pre = f[pre];
			if(a[pre + 1] == a[i]) pre ++;
			f[i] = pre;
		}
		rep(i, 0, n - 1) rep(j, 1, m) {
			int pre = i;
			while(pre && a[pre + 1] != j) pre = f[pre];
			if(a[pre + 1] == j) pre ++;
			s[pre][i] ++;
		}
		s[n + 1][n] = 1;
		s[n + 1][n + 1] = m;
		mat seed = s;
		s = pow_(s, l + 1);
		cout << (s[n + 1][0] + MOD) % MOD << "\n";
		
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, l;
	cin >> n >> m >> l;
	init_(n, m, l);
	rep(i, 1, n) cin >> a[i];
	solve();
	return 0;
}


