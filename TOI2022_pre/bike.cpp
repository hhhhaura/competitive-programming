#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
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
#define print(a...) cerr<<"LINE"<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() {cerr << endl;}
template<class T1, class ...T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, k, ans;
	vector<vector<pii>> mp;
	vector<int> a;
	void init_(int _n, int _k) {
		n = _n, k = _k, ans = 0;
		a.assign(n + 1, 0);
		mp.assign(n + 1, vector<pii>());
	}
	int dfs(int x, int par) {
		int cur = a[x] - k;
		for(auto i : mp[x]) if(i.x != par) {
			int cnt = dfs(i.x, x);
			ans += abs(cnt) * i.y;
			cur += cnt;
		}
		return cur;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n - 1) {
		int x, y, d;
		cin >> x >> y >> d;
		mp[x].push_back({y, d});
		mp[y].push_back({x, d});
	}
	dfs(1, 1);
	cout << ans << "\n";
	return 0;
}
/*
8 2 
4 2 2 1 3 3 0 1
1 2 3
2 3 1
3 4 2
5 6 2
6 7 3
6 8 1
2 6 3

*/

