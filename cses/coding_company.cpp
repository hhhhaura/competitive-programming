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
	int n, x;
	const int p = 10000;
	cin >> n >> x;
	vector<int> a(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	vector<vector<int>> nxt, cur;
	auto add = [](int &a, int b) {
		a = (a + b) % MOD;
	};
	int sum = 0;
	cur.assign(n + 1, vector<int>(p + x + 2, 0));
	sort(all(a));
	cur[0][p] = 1;
	rep(i, 1, n) {
		sum += a[i];
		nxt.assign(n + 1, vector<int>(p + x + 2, 0));
		rep(j, 0, i) rep(k, p - sum, p + min(sum, x)) {
			if(j < n && a[i] <= k) add(nxt[j][k], 
				cur[j + 1][k - a[i]] * (j + 1) % MOD);
			if(j && a[i] + k <= x + p) add(nxt[j][k], cur[j - 1][k + a[i]]);
			add(nxt[j][k], cur[j][k] * (j + 1) % MOD);
			//if(nxt[j][k]) print(i, j, k - p, nxt[j][k]);
		}
		cur = nxt;
	}
	int ans = 0;
	rep(i, 0, x) add(ans, cur[0][i + p]);
	cout << ans << "\n";
	return 0;
}


