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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<lld> p(n + 1, 0);
	rep(i, 1, n) {
		int x; cin >> x;
		p[i] = x / 1000000.0;
	}
	cerr << fixed << setprecision(10);
	lld L = 0, R = 1e9;
	rep(t, 1, 90) {
		lld mid = (L + R) / 2, ans = 0;
		rep(i, 1, n) {
			lld cur = (n - 1) * p[i] + (1 - p[i]) * (mid * n + n - 1);
			ans += cur / (lld) (n - p[i]);
		}
		ans /= n;
		if(ans < mid) R = mid;
		else L = mid;
	}
	cout << fixed << setprecision(9);
	cout << L << "\n";
	return 0;
}

