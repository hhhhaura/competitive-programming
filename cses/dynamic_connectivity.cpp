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
namespace solver {
	int n, m, cnt, op;
	vector<int> par, sz, ans;
	vector<vector<pii>> v;
	map<pii, int> mp;
	vector<pair<int*, int>> st;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		cnt = n, op = 0;
		par.assign(n + 1, 0);
		iota(all(par), 0);
		sz.assign(n + 1, 1);
		ans.assign(m + 1, 0);
		v.assign(2 * (m + 1), vector<pii>());
	}
	void undo() {
		op --, cnt ++;
		pair<int*, int> a = st.back(); st.pop_back();
		pair<int*, int> b = st.back(); st.pop_back();
		*a.x = a.y, *b.x = b.y;
	}
	int find_par(int a) {
		while(par[a] != a) a = par[a];
		return a;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		cnt--, op++;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		st.push_back({&sz[aa], sz[aa]});
		st.push_back({&par[bb], par[bb]});
		sz[aa] += sz[bb];
		par[bb] = aa;
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void modify(int L, int R, int l, int r, pii p) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) v[nd].push_back(p);
		else modify(L, mid, l, r, p), modify(mid + 1, R, l, r, p);
	}
	void operate(int L, int R) {
		int cur = op, mid = (L + R) / 2;
		for(auto i : v[get(L, R)]) unite(i.x, i.y);
		if(L == R) ans[L] = cnt;
		else operate(L, mid), operate(mid + 1, R);
		while(op != cur) undo();
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	init_(n, q);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		if(a > b) swap(a, b);
		mp[pii(a, b)] = 0;
	}
	rep(i, 1, q) {
		int t, a, b;
		cin >> t >> a >> b;
		if(a > b) swap(a, b);
		if(t == 1) mp[pii(a, b)] = i;
		else {
			assert(mp.find(pii(a, b)) != mp.end());
			auto it = mp.find(pii(a, b));
			modify(0, q, it->y, i - 1, pii(a, b));
			mp.erase(it);
		}
	}
	for(auto i : mp) modify(0, q, i.y, q, i.x);
	operate(0, q);
	rep(i, 0, q) cout << ans[i] << " \n"[i == q];

	return 0;
}


