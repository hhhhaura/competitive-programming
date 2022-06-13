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
	const int P = 10;
	const int tot = 100;
	vector<int> to;
	vector<int> v = { 10, 8, 18, 28, 9, 21, 6, 24, 23, 29 };
	mat make_mat(int x) { return vector<vector<int>>(x, vector<int>(x, 0)); }
	void init_(int _n, int _k, int _x) {
		n = _n, k = _k, x = _x;
		to.assign(tot, 0);
		rep(i, 0, tot - 1) {
			int a = i % 10, b = i / 10;
			to[i] = v[a] | (v[b] << 5);
		}
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
				int val = __builtin_popcount(to[i] ^ to[j]);
				d[i][j] = tp[0][val];
			}
			c = mul(d, c, tot);
		}
		rep(i, 0, tot - 1) cout << c[i][x] << "\n"; 
	}
};
namespace solver1 {
	int n, k, x;
	const int P = 5;
	const int tot = 32;
	mat id, a, b;
	vector<int> v = {
		10, 8, 18, 28, 9,
		21, 6, 24, 23, 29
	};
	void init_(int _n, int _k, int _x) {
		n = _n, k = _k, x = _x;
		id.assign(tot, vector<int>(tot, 0));
		rep(i, 0, tot - 1) id[i][i] = 1;
		a.assign(tot, vector<int>(tot, 0));
		b.assign(tot, vector<int>(tot, 0));
		rep(i, 0, tot - 1) rep(j, 0, P - 1) {
			a[i ^ (1 << j)][i] = 1;
		}
		b = a;
		rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
			int yes = 0;
			rep(k, 0, 9) if(i == v[k]) yes = 1;
			if(!yes) b[i][j] = 0;
		}
	}
	mat mul(mat a, mat b) {
		mat ans(tot, vector<int>(tot, 0));
		rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
			rep(k, 0, tot - 1) ans[i][j] += a[i][k] * b[k][j] % MOD;
			ans[i][j] %= MOD;
		}
		return ans;
	}
	mat pow_(mat a, int times) {
		mat ans = id;
		for(; times > 0; times >>= 1, a = mul(a, a)) {
			if(times & 1) ans = mul(a, ans);
		}
		return ans;
	}
	void solve() {
		mat c = mul(b, pow_(a, k - 1));
		mat d = pow_(c, n / k);
		if(n % k) {
			d = mul(pow_(a, (n - 1) % k), d);
			d = mul(b, d);
		}
		vector<int> ans(tot, 0), sum(10, 0);
		ans[v[x]] = 1;
		rep(i, 0, tot - 1) {
			int val = 0;
			rep(j, 0, tot - 1) val += ans[j] * d[i][j] % MOD;
			rep(j, 0, 9) if(v[j] == i) sum[j] = val;
		}
		rep(i, 0, 9) cout << sum[i] << "\n";
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int m, n, k, x;
	cin >> m >> n >> k >> x;
	if(m == 1) {
		solver1::init_(n, k, x);
		solver1::solve();
	}
	else {
		solver2::init_(n, k, x);
		solver2::solve();
	}
	return 0;
}


