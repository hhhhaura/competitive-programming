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
namespace solver {
	int n;
	vector<vector<int>> v, a;
	int lowbit(int x) {
		return x & (-x);
	}
	void modify2(int id, int x, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			v[id][i] += val;
		}
	}
	void modify1(int x, int y, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			modify2(i, y, val);
		}
	}
	int query2(int id, int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += v[id][i];
		}
		return ans;
	}
	int query1(int x, int y) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += query2(i, y);
		}
		return ans;
	}
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, vector<int>(n + 1, 0));
		v.assign(n + 1, vector<int>(n + 1, 0));
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n);
	rep(i, 1, n) rep(j, 1, n) {
		char c; cin >> c;
		if(c == '*') modify1(i, j, 1), a[i][j] = 1;
	}
	rep(i, 1, q) {
		int tp; cin >> tp;
		if(tp == 1) {
			int x, y;
			cin >> x >> y;
			if(a[x][y]) modify1(x, y, -1);
			else modify1(x, y, 1);
			a[x][y] ^= 1;
		}
		else {
			int u, d, l, r;
			cin >> u >> l;
			cin >> d >> r;
			if(u > d) swap(u, d);
			if(l > r) swap(l, r);
			int ans = query1(d, r) - query1(d, l - 1)
				- query1(u - 1, r) + query1(u - 1, l - 1);
			cout << ans << "\n";
		}
	}
	return 0;
}


