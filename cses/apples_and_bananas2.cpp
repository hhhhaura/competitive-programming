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
#define eps (1e-6)
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
#define cp complex<lld>
struct FFT {
	int n, k;
	const lld PI = acos(-1);
	vector<cp> omg, iomg;
	vector<int> inv;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		cp p = {cos(2 * PI / n), sin(2 * PI / n)};
		omg.assign(n, {1, 0});
		iomg.assign(n, {1, 0});
		inv.assign(n, 0);
		rep(i, 1, n - 1) omg[i] = omg[i - 1] * p;
		rep(i, 1, n - 1) iomg[i] = omg[n - i];
		rep(i, 0, n - 1) rep(j, 0, k - 1) {
			inv[i] |= (((i >> j) & 1) << (k - 1 - j));
		}

	}	
	void transform(vector<cp> &v, vector<cp> &omg) {
		rep(i, 0, n - 1) if(inv[i] < i) swap(v[i], v[inv[i]]);
		for(int len = 1; len < n; len <<= 1) {
			int to = n / (len << 1);
			for(int i = 0; i < n; i += 2ll * len) {
				for(int j = i; j < i + len; j ++) {
					int val = (j - i) * to; 
					cp x = v[j], y = v[j + len] * omg[val];
					v[j] = x + y;
					v[j + len] = x - y;
				}
			}
		}
	}
	void fft(vector<cp> &v) { transform(v, omg); }
	void ifft(vector<cp> &v) {
		transform(v, iomg);
		rep(i, 0, n - 1) v[i] /= n;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int k, n, m;
	cin >> k >> n >> m;
	int lg = 32 - __builtin_clz(2 * k + 1);
	int tot = 1 << lg;
	print(lg, tot);
	vector<cp> a(tot, 0);
	vector<cp> b(tot, 0);
	rep(i, 1, n) {
		int x; cin >> x;
		a[x] += 1;
	}
	rep(i, 1, m) {
		int x; cin >> x;
		b[x] += 1;
	}	
	FFT fft; 
	fft.init_(tot, lg);
	fft.fft(a);
	fft.fft(b);
	rep(i, 0, tot - 1) a[i] = a[i] * b[i];
	fft.ifft(a);
	rep(i, 2, 2 * k) cout << (ll)round(a[i].real() + eps) << " \n"[i == 2 * k];
	return 0;
}



