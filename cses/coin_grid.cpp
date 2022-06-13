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
	int n, ii;
	vector<vector<int>> mp;
	vector<int> mx, my, vx, vy;
	void init_(int _n) {
		n = _n, ii = 0;
		mp.assign(n + 1, vector<int>());
		mx.assign(n + 1, -1);
		my.assign(n + 1, -1);
		vx.assign(n + 1, 0);
		vy.assign(n + 1, 0);
	}
	int dfs(int x) {
		for(auto i : mp[x]) if(vy[i] != ii) {
			vy[i] = ii;
			if(my[i] == -1 || dfs(my[i])) {
				my[i] = x;
				mx[x] = i;
				return 1;
			}
		}
		return 0;
	}
	void traverse(int x) {
		if(vx[x] == ii) return;
		vx[x] = ii;
		for(auto i : mp[x]) {
			vy[i] = ii;
			traverse(my[i]);
		}
	}
	void solve() {
		rep(i, 1, n) rep(j, 1, n) {
			char c; cin >> c;
			if(c == 'o') mp[i].push_back(j);
		}
		int ans = 0;
		rep(i, 1, n) ii++, ans += dfs(i);
		ii ++;
		rep(i, 1, n) if(mx[i] == -1) traverse(i);
		cout << ans << "\n";
		rep(i, 1, n) if(vx[i] != ii) cout << 1 << " " << i << "\n";
		rep(i, 1, n) if(vy[i] == ii) cout << 2 << " " << i << "\n";
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	solve();
	return 0;
}


