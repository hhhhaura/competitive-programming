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
#define MOD 998244353
#define eps (1e-9)
#define ll long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr << "Line " << __LINE__, kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif

struct NTT {
	const int p = 15311432, n = 1 << 23;
	const int g = 3, k = 23, r = 119;
	const int inv_n = 998244234;
	vector<int> omg, iomg, inv;
	void init_() {
		omg.assign(n, 1);
		iomg.assign(n, 1);
		inv.assign(n, 0);
		rep(i, 1, n - 1) omg[i] = (ll) omg[i - 1] * p % MOD;
		rep(i, 1, n - 1) iomg[i] = omg[n - i];
		rep(i, 0, n - 1) rep(j, 0, k - 1) {
			inv[i] |= (((i >> j) & 1) << (k - 1 - j));
		}

	}	
	void transform(vector<int> &v, vector<int> &omg) {
		rep(i, 0, n - 1) if(inv[i] < i) swap(v[i], v[inv[i]]);
		for(int len = 1; len < n; len <<= 1) {
			int to = n / (len << 1);
			for(int i = 0; i < n; i += 2ll * len) {
				for(int j = i; j < i + len; j ++) {
					int val = (j - i) * to; 
					int x = v[j], y = (ll)v[j + len] * omg[val] % MOD;
					v[j] = (x + y >= MOD ? x + y - MOD : x + y);
					v[j + len] = (x - y < 0 ? x - y + MOD : x - y);
				}
			}
		}
	}
	void fft(vector<int> &v) { transform(v, omg); }
	void ifft(vector<int> &v) {
		transform(v, iomg);
		rep(i, 0, n - 1) v[i] = (ll)v[i] * inv_n % MOD;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int k, n, m;
	const int tot = 1 << 23;
	cin >> k >> n >> m;
	vector<int> a(tot, 0);
	vector<int> b(tot, 0);
	rep(i, 1, n) {
		int x; cin >> x;
		a[x] ++;
	}
	rep(i, 1, m) {
		int x; cin >> x;
		b[x] ++;
	}	
	NTT ntt; 
	ntt.init_();
	ntt.fft(a);
	ntt.fft(b);
	rep(i, 0, tot - 1) a[i] = (ll)a[i] * b[i] % MOD;
	ntt.ifft(a);
	rep(i, 2, 2 * k) cout << (a[i] + MOD) % MOD << " \n"[i == 2 * k];
	return 0;
}


