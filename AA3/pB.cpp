#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define ramdon mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 100000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<__LINE__<<": ",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L)==R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ...e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, c;
	const int P = 200;
	vector<int> a;
	vector<vector<pii>> mp;
	vector<vector<int>> dp, cost;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		cost.assign(n + 1, vector<int>(P + 1, INF));
		mp.assign(n + 1, vector<pii>());
		dp.assign(n + 1, vector<int>(2 * P + 1, INF));
	}
	void dfs(int x, int par) {
		dp[x][a[x] + P] = 0;
		for(auto es : mp[x]) if(es.first != par) {
			int to = es.first, v = es.second;
			dfs(to, x);
			vector<int> tp(2 * P + 1, INF);
			rrep(i, -P, P) {
				rep(j, max(i - P, -P), min(i + P, P)) tp[i + P] = 
					min(tp[i + P], v * abs(j)  + dp[to][j + P] + dp[x][i - j + P]);
			}
			dp[x] = tp;
		}
		vector<int> ans(2 * P + 1, INF);
		rep(i, -P, P) rep(j, 0, min({P - i, c})) {
			ans[i + P] = min(ans[i + P], dp[x][j + i + P] + cost[x][j]);
		}
		dp[x] = ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b, cost;
		cin >> a >> b >> cost;
		mp[a].push_back({b, cost});
		mp[b].push_back({a, cost});
	}
	cin >> c;
	rep(i, 1, n) cost[i][0] = 0;
	rep(i, 1, n) rep(j, 1, c) 
		cin >> cost[i][j];
	int k; cin >> k;
	rep(i, 1, k) {
		int x; cin >> x;
		a[x] ++;
	}
	dfs(1, 1);
	cout << dp[1][P] << "\n";
	return 0;
}


