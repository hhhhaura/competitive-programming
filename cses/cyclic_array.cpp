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
	int n, k, lg;
	cin >> n >> k;
	lg = 31 - __builtin_clz(n);
	vector<int> a(2 * n + 1, 0);
	vector<vector<int>> to(lg + 1, vector<int>(2 * n + 1, 0));
	int l = 1, sum = 0;
	rep(i, 1, n) cin >> a[i];
	rep(i, n + 1, 2 * n) a[i] = a[i - n];
	rep(i, 1, 2 * n) {
		sum += a[i];
		while(sum > k) sum -= a[l ++];
		to[0][i] = l - 1;
	}
	rep(i, 1, lg) rep(j, 1, 2 * n) {
		to[i][j] = to[i - 1][to[i - 1][j]];
	}
	int ans = INF;
	rep(i, n + 1, 2 * n) {
		int cur = i, cnt = 0;
		rrep(j, 0, lg) if(to[j][cur] > i - n) 
			cur = to[j][cur], cnt += 1 << j;
		cnt += 1;
		ans = min(ans, cnt);
	}
	cout << ans << "\n";
	return 0; 
}


