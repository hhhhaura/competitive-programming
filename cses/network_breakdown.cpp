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
	int n, m, cnt, k;
	vector<int> x, y, par, rk; 
	set<pii> s;
	void init_(int _n, int _m, int _k) {
		n = _n, m = _m;
		cnt = n, k = _k;
		x.assign(m + 1, 0);
		y.assign(m + 1, 0);
		par.assign(n + 1, 0);
		iota(all(par), 0);
		rk.assign(n + 1, 0);
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		cnt --;
		if(rk[bb] > rk[aa]) swap(aa, bb);
		par[bb] = aa;
		rk[aa] += (rk[aa] == rk[bb]);
	}
	void solve() {
		rep(i, 1, m) {
			cin >> x[i] >> y[i];
			if(x[i] > y[i]) swap(x[i], y[i]);
		}
		vector<pii> v;
		rep(i, 1, k) {
			int a, b;
			cin >> a >> b;
			if(a > b) swap(a, b);
			s.insert({a, b});
			v.push_back({a, b});
		}
		rep(i, 1, m) if(s.find({x[i], y[i]}) == s.end()) {
			unite(x[i], y[i]);
		}
		print(cnt);
		reverse(all(v));
		vector<int> ans;
		for(auto i : v) {
			ans.push_back(cnt);
			unite(i.x, i.y);
		}
		rrep(i, 0, signed(ans.size()) - 1) 
			cout << ans[i] << " \n"[i == 0];
	}
};

using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	init_(n, m, k);
	solve();
	return 0;
}


