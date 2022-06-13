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
namespace solver {
	int n;
	random;
	vector<vector<int>> mp;
	vector<int> pre, dep;
	void init_(int _n) {
		n = _n;
		dep.assign(n + 1, 0);
		rep(i, 1, n) dep[i] = rnd() % 65536;
	}
	int dfs(int x, int par, int d) {
		int ans = 1;
		vector<int> v;
		for(auto i : mp[x]) if(i != par) {
			v.push_back(dfs(i, x, d + 1));
		}
		sort(all(v));
		int cur = dep[d];
		for(auto i : v) {
			ans = (ans + cur * i % MOD) % MOD;
			cur = cur * dep[d] % MOD;
		}
		print(x, ans);
		vprint(all(v));
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		mp.assign(n + 1, vector<int>());
		rep(i, 1, n - 1) {
			int a, b;
			cin >> a >> b;
			mp[a].push_back(b);
			mp[b].push_back(a);
		}
		int val1 = dfs(1, 1, 1);
		mp.assign(n + 1, vector<int>());
		rep(i, 1, n - 1) {
			int a, b;
			cin >> a >> b;
			mp[a].push_back(b);
			mp[b].push_back(a);
		}
		int val2 = dfs(1, 1, 1);
		if(val1 == val2) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}


