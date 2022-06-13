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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int x, y; cin >> x >> y;
	int n; cin >> n;
	assert(n == 2);
	int a, b, c, v1, v2;
	cin >> c >> c;
	a = c, b = x - c;
	cin >> c >> v1 >> v2;
	lld L = 0, R = y;
	auto cal = [&](lld xx) {
		lld ll = sqrt(xx * xx + a * a) / (lld) v1;
		lld rr = sqrt((y - xx) * (y - xx) + b * b) / (lld) v2;
		return ll + rr;
	};
	rep(i, 0, 100) {
		lld v = (R - L) / 3;
		if(cal(L + v) > cal(R - v)) L = L + v;
		else R = R - v;

	}
	cout << fixed << setprecision(10);
	cout << cal(L) << "\n";
	return 0;
}

