#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n;
	vector<vector<int>> dp, a, b;
	vector<pair<int, pii>> es;
	void init_(int _n) {
		n = _n;
		a.assign(n + 2, vector<int>(n + 2, INF));
		b.assign(n + 2, vector<int>(n + 2, INF));
		dp.assign(n + 2, vector<int>(n + 2, INF));
		es.clear();
	}
	void solve() {
		dp[1][1] = 0;
		rep(i, 1, n) rep(j, 1, n) {
			if(i <= j) {
				dp[j + 1][j] = min(dp[j + 1][j], dp[i][j] + a[i][j + 1]);
				dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + b[j][j + 1]);
			}
			if(j <= i) {
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + a[i][i + 1]);
				dp[i][i + 1] = min(dp[i][i + 1], dp[i][j] + b[j][i + 1]);
			}
		}
		int ans = INF;
		for(auto i : es) if(max(i.y.x, i.y.y) == n)
			ans = min(ans, dp[i.y.x][i.y.y] + i.x);
		cout << (ans == INF ? -1 : ans)  << "\n";
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int x, y, c;
		cin >> x >> y >> c;
		if(x < 0) b[-y][-x] = min(b[-y][-x], c);
		else if(y > 0) a[x][y] = min(a[x][y], c);
		else es.push_back({c, {x, -y}});
	}
	solve();
	return 0;
}




