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
#define x first
#define y second
struct BIT {
	int n;
	vector<int> v;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & (-x);
	}
	void modify(int x, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			v[i] += val;
		}
	}
	int query(int x) {
		int ans = 0;
		if(x <= 0) return 0;
		x = min(n, x);
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += v[i];
		}
		return ans;
	}
};
namespace solver {
	int n, L, R, ans;
	vector<vector<int>> mp;
	vector<int> sz, mx, cnt, vis;
	void init_(int _n, int _L, int _R) {
		n = _n, L = _L, R = _R, ans = 0;
		mp.assign(n + 1, vector<int>());
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		vis.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) if(i != par) {
			if(vis[i]) continue;
			get_sz(i, x);
			sz[x] += sz[i];
			mx[x] = max(mx[x], sz[i]);
		}
	}
	int get_cen(int x, int par, int tot) {
		int best = x;
		for(auto i : mp[x]) if(i != par) {
			if(vis[i]) continue;
			int cur = get_cen(i, x, tot);
			if(max(tot - sz[best], mx[best]) 
				> max(tot - sz[cur], mx[cur])) best = cur;
		}
		return best;
	}
	void dfs(int x, int par, int dep) {
		cnt[dep] ++;
		for(auto i : mp[x]) if(i != par) {
			if(vis[i]) continue;
			dfs(i, x, dep + 1);
		}
	}
	void deco(int x) {
		get_sz(x, x);
		int cen = get_cen(x, x, sz[x]);
		vis[cen] = 1;
		get_sz(cen, cen);
		BIT bit; bit.init_(sz[cen]);
		for(auto i : mp[cen]) {
			if(vis[i]) continue;
			cnt.assign(sz[i] + 1, 0);
			dfs(i, cen, 1);
			rep(j, 1, sz[i]) {
				if(j <= R && j >= L) ans += cnt[j];
				ans += (bit.query(R - j) - bit.query(L - 1 - j)) * cnt[j];
			}
			rep(j, 1, sz[i]) bit.modify(j, cnt[j]);
		}
		for(auto i : mp[cen]) {
			if(vis[i]) continue;
			deco(i);
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, L, R;
	cin >> n >> L >> R;
	init_(n, L, R);
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	deco(1);
	cout << ans << "\n";

	return 0;
}


