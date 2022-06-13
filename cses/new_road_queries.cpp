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
namespace dsu {
	int n, m;
	vector<int> par, sz, ans;
	vector<unordered_set<int>> v;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		par.assign(n + 1, 0);
		iota(all(par), 0);
		sz.assign(n + 1, 1);
		ans.assign(m + 1, -1);
		v.assign(n + 1, unordered_set<int>());
	}
	int find_par(int x) {
		while(x != par[x]) x = par[x];
		return x;
	}
	void unite(int a, int b, int t) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		sz[aa] += sz[bb];
		par[bb] = aa;
		if(v[aa].size() < v[bb].size()) v[aa].swap(v[bb]);
		for(auto i : v[bb]) {
			if(v[aa].find(i) != v[aa].end()) {
				ans[i] = t;
				v[aa].erase(v[aa].find(i));
			}
			else v[aa].insert(i);
		} 
		v[bb].clear();
	}

};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	dsu::init_(n, q);
	vector<pii> es;
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		es.push_back({a, b});
	}
	rep(i, 1, q) {
		int a, b;
		cin >> a >> b;
		if(a == b) dsu::ans[i] = 0;
		else {
			dsu::v[a].insert(i);
			dsu::v[b].insert(i);
		}
	}
	rep(i, 1, m) dsu::unite(es[i - 1].x, es[i - 1].y, i);
	rep(i, 1, q) cout << dsu::ans[i] << "\n";

	return 0;
}


