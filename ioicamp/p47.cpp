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
#define pos(x) get(x, x)
namespace solver {
	int n, timestamp, ii, tot, scc;
	vector<int> inv, pre, instack, L, D, id;
	vector<pii> a;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n, tot = 2 * n;
		inv.assign(tot, 0);
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void build(int L, int R, int par) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(par != -1) mp[par].push_back(nd);
		if(L != R) {
			build(L, mid, nd);
			build(mid + 1, R, nd);
		}
	}
	void modify(int L, int R, int l, int r, int x) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) mp[pos(x)].push_back(nd);
		else {
			modify(L, mid, l, r, x);
			modify(mid + 1, R, l, r, x);
		}
	}
	void dfs(int x) {
		L[x] = D[x] = ++ timestamp;
		instack[x] = 1, pre[ii++] = x;
		for(auto i : mp[x]) {
			if(!D[i]) {
				dfs(i);
				L[x] = min(L[x], L[i]);
			}
			else if(instack[i]) L[x] = min(L[x], D[i]);
		}
		if(L[x] ==  D[x]) {
			scc++;
			while(pre[ii] != x) {
				ii--;
				id[pre[ii]] = scc;
				instack[pre[ii]] = 0;
			}
		}
	}
	bool calculate(int x) {
		timestamp = 0, ii = 0, scc = 0;
		pre.assign(2 * tot, -1), id.assign(2 * tot - 1, 0);
		instack.assign(2 * tot - 1, 0);
		L.assign(2 * tot - 1, 0), D.assign(2 * tot - 1, 0);
		mp.assign(2 * tot - 1, vector<int>());
		build(0, tot - 1, -1);
		rep(i, 0, tot - 1) {
			int L, R, val = a[i].first, to = a[i].second;
			L = upper_bound(all(a), pii(val - x, INF)) - a.begin();
			R = lower_bound(all(a), pii(val + x, -INF)) - a.begin() - 1;
			if(L < i && i > 0) modify(0, tot - 1, L, i - 1, inv[to]);
			if(R > i) modify(0, tot - 1, i + 1, R, inv[to]);
		}
		rep(i, 0, 2 * tot - 2) if(!D[i]) dfs(i);
		rep(i, 0, n - 1) if(id[pos(inv[i])] == id[pos(inv[n + i])]) return 0;
		return 1;
	}
	void solve() {
		sort(all(a));
		if(n == 1) {
			cout << "1000000000\n";
			return;
		}
		rep(i, 0, tot - 1) {
			int val = a[i].first, to = a[i].second;
			if(to >= n) inv[to - n] = i;
			else inv[to + n] = i;
		}
		int L = 0, R = 1000000001;
		while(R - L > 1) {
			int mid = (L + R) / 2;
			if(calculate(mid)) L = mid;
			else R = mid;
		}
		cout << L << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) {
		int x, y;
		cin >> x >> y;
		a.push_back({x, i});
		a.push_back({y, i + n});
	}
	solve();
	return 0;
}

