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
	vector<int> inv;
	vector<cp> omg, iomg;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		cp p = {cos(2 * PI / n), sin(2 * PI / n)};
		omg.assign(n, 1);
		iomg.assign(n, 1);
		inv.assign(n, 0);
		rep(i, 1, n - 1) omg[i] = omg[i - 1] * p;
		rep(i, 1, n - 1) iomg[i] = omg[n - i];
		rep(i, 0, n - 1) rep(j, 0, k - 1) {
			inv[i] |= (((i >> j) & 1) << (k - 1 - j));
		}
	}
	void transform(vector<cp> &v, vector<cp> &omg) {
		rep(i, 0, n - 1) if(i < inv[i]) swap(v[i], v[inv[i]]);
		for(int len = 1; len < n; len <<= 1) {
			int to = (n / len) >> 1;
			for(int i = 0; i < n; i += 2 * len) {
				for(int j = i; j < i + len; j ++) {
					cp x = v[j], y = v[j + len] * omg[(j - i) * to];
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
	int x, y;
	cin >> x >> y;
	int k = 32 - __builtin_clz(x + y + 1);
	int n = 1 << k;
	FFT fft; 
	fft.init_(n, k);
	vector<cp> a(n, 0);
	vector<cp> b(n, 0);
	rep(i, 0, x - 1) {
		int val; cin >> val;
		a[i] = val;
	}
	rep(i, 0, y - 1) {
		int val; cin >> val;
		b[y - i - 1] = val;
	}
	fft.fft(a), fft.fft(b);
	rep(i, 0, n - 1) a[i] *= b[i];
	fft.ifft(a);
	rep(i, 1 - y, x - 1) cout << (int)abs(round(a[i + y - 1].real())) 
		<< " \n"[i + 1 == x];
	return 0;	
}



