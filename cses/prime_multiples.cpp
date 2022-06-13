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
#define ll __int128
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(k, 0);
	int ans = 0;
	rep(i, 0, k - 1) cin >> a[i];
	rep(i, 1, (1 << k) - 1) {
		int sz = __builtin_popcount(i);
		int cur = 1, bad = 0;
		rep(j, 0, k - 1) if((i >> j) & 1) {
			ll to = (ll) cur * a[j];
			if(to > n) bad = 1;
			else cur = to;
		} 
		if(!bad) ans += ((sz & 1) ? 1 : -1) * n / cur;
	}
	cout << ans << "\n";
	return 0;
}


