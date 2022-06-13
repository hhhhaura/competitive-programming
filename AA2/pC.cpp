#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__, kout("["+string(#a)+"] = ", a)
void kout() { cerr << endl; }
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, L, R;
	cin >> n >> L >> R;
	int m = n / 2;
	vector<int> a(n, 0), x, y;
	rep(i, 0, n - 1) cin >> a[i];
	rep(i, 0, (1 << m) - 1) {
		int ans = 0;
		rep(j, 0, m - 1) ans += ((i >> j) & 1) * a[j];
		x.push_back(ans);
	}
	rep(i, 0, (1 << (n - m)) - 1) {
		int ans = 0 ;
		rep(j, m, n - 1) ans += ((i >> (j - m)) & 1) * a[j];
		y.push_back(ans);
	}
	sort(all(x));
	sort(all(y));
	int tot = (int) x.size() * (int) y.size();
	L = tot - L + 1;
	R = tot - R + 1;
	swap(L, R);
	auto binsch = [&](int val) {
		int L = 0, R = 1e12;
		reverse(all(x));
		while(R - L > 1) {
			int mid = (L + R) / 2;
			int ans = 0, ii = 0;
			for(auto i : x) {
				while(ii < y.size() && mid - i >= y[ii]) ii++;
				ans += ii;
			}
			if(ans >= val) R = mid;
			else L = mid;
		}
		reverse(all(x));
		return R;
	};
	auto calculate = [&](int val) {
		int ans = 0;
		for(auto i : x) ans += lower_bound(all(y), val - i) - y.begin();
		return ans;
	};
	vector<int> v;
	int l = binsch(L) + 1, r = binsch(R) - 1;
	int s = calculate(l) - L + 1, t = R - calculate(r + 1);
	for(auto i : x) {
		int a = lower_bound(all(y), l - i) - y.begin();
		int b = upper_bound(all(y), r - i) - y.begin() - 1;
		rep(j, a, b) v.push_back(i + y[j]);
	}
	sort(all(v)), reverse(all(v));
	if(l - 1 == r + 1) rep(i, L, R) cout << l - 1 << " \n"[i == R];
	else {
		rep(i, 1, t) cout << r + 1 << " ";
		rep(i, 0, signed(v.size()) - 1) cout << v[i] << " ";
		rep(i, 1, s) cout << l - 1 << " \n"[i == t];
	}
	return 0;
}


