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
struct BIT {
	int n;
	vector<int> v;
	void init_(int _n) {
		n = _n;
		v.assign(2 * n + 1, 0);
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void modify(int L, int R, int x, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = val;
		else {
			if(x <= mid) modify(L, mid, x, val);
			else modify(mid + 1, R, x, val);
			v[nd] = max(v[get(L, mid)], v[get(mid + 1, R)]);		
		}
	}
	int query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		else if(l <= L && r >= R) return v[nd];
		else return max(query(L, mid, l, r), query(mid + 1, R, l, r));
	}
};
namespace solver {
	int n, timestamp;
	BIT bit;
	vector<vector<int>> mp;
	vector<int> v, id, mx, top, par, sz;
	void init_(int _n) {
		n = _n, timestamp = 0;
		mp.assign(n + 1, vector<int>());
		v.assign(n + 1, 0);
		id.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		top.assign(n + 1, 0);
		par.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		bit.init_(n);
	}
	void dfs(int x, int p) {
		par[x] = p, sz[x] = 1;
		for(auto i : mp[x]) if(i != p) {
			dfs(i, x);
			sz[x] += sz[i];
			if(sz[i] > sz[mx[x]]) mx[x] = i;
		}
	}
	void deco(int x, int p, int tp) {
		id[x] = ++timestamp;
		top[x] = tp;
		bit.modify(1, n, timestamp, v[x]);
		if(mx[x]) deco(mx[x], x, tp);
		for(auto i : mp[x]) if(i != p) {
			if(i == mx[x]) continue;
			deco(i, x, i);
		}
	}
	void modify(int x, int val) {
		bit.modify(1, n, id[x], val);
		v[x] = val;
	}
	int query(int a, int b) {
		int ans = 0;
		while(top[a] != top[b]) {
			if(id[top[a]] < id[top[b]]) swap(a, b);
			int to = top[a];
			ans = max(ans, bit.query(1, n, id[to], id[a]));
			a = par[top[a]];
		}
		if(id[a] > id[b]) swap(a, b);
		ans = max(ans, bit.query(1, n, id[a], id[b]));
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n);
	rep(i, 1, n) cin >> v[i];
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	dfs(1, 1);
	deco(1, 1, 1);
	while(q--) {
		int tp, x, y; 
		cin >> tp >> x >> y;
		if(tp == 1) modify(x, y);
		else cout << query(x, y) << "\n";
	}
	return 0;
}



