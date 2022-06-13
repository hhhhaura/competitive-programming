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
	int n, ans, tot;
	vector<int> a;
	vector<vector<int>> mp;
	map<int, int> cnt[2];
	void init_(int _n) {
		n = _n, ans = 0, tot = 0;
		a.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
	}
	int dfs(int x) {
		int par = 0;
		for(auto i : mp[x]) {
			par = dfs(i) ^ 1;
		}
		cnt[par][a[x]] ++;
		if(!par) ans ^= a[x], tot ++;
		return par;
	}
	int C(int n) {
		return (n - 1) * n / 2;
	}
	void solve() {
		dfs(1);
		int yes = 0;
		if(ans) {
			for(auto i : cnt[0]) {
				int a = i.second;
				int b = cnt[1][ans ^ i.first];
				yes += a * b;
			}
		}
		else {
			yes += C(tot) + C(n - tot);
			for(auto i : cnt[0]) {
				int a = i.second;
				int b = cnt[1][i.first];
				yes += a * b;
			}
		}
		cout << yes << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) {
		int x; cin >> x;
		mp[x].push_back(i);
	}
	solve();
	return 0;
}


