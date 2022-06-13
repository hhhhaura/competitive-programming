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
	int n, q, ops;
	vector<vector<pii>> evt;
	vector<int> par, sz, cnt, ans, st;
	vector<vector<int>> v;
	vector<pii> b;
	vector<pair<int, pii>> a;
	set<int> s;
	vector<pair<int*, int>> c;
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void init_(int _n, int _q) {
		n = _n, q = _q, ops = 0;
		evt.assign(2 * q + 1, vector<pii>());
		par.assign(n + 1, 0);
		sz.assign(n + 1, 1);
		cnt.assign(n + 1, 1);
		ans.assign(n + 1, 0);
		v.assign(n + 1, vector<int>());
		rep(i, 1, n) {
			par[i] = i;
			s.insert(i);
			v[i].push_back(i);
		}
	}
	void modify(int L, int R, int l, int r, pii v) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) evt[nd].push_back(v);
		else modify(L, mid, l, r, v), modify(mid + 1, R, l, r, v);
	}
	int find_par(int x) {
		while(par[x] != x) x = par[x];
		return par[x];
	}
	void do_type1(int x, int from, int to) {
		ops ++, st.push_back(1);
		v[to].push_back(x);
		a.push_back({x, {from, to}});
	}
	void do_type2(int tp, int x) {
		ops ++, st.push_back(2);
		if(tp == 1) s.insert(x);
		else if(s.find(x) != s.end()) s.erase(s.find(x));
		b.push_back({tp, x});
	}
	void do_type3(int* x, int y) {
		ops ++, st.push_back(3);
		c.push_back({x, y});
	}
	void change(int x, int val) {
		int a = find_par(x);
		do_type3(&cnt[a], cnt[a]);
		if(!cnt[a]) do_type2(1, a);
		cnt[a] += val;
		if(!cnt[a]) do_type2(0, a);
	}
	int unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		int ini = ops;
		if(aa == bb) return 0;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		//
		if(cnt[bb]) do_type2(0, bb);
		if(!cnt[aa] && cnt[bb]) do_type2(1, aa);
		do_type3(&sz[aa], sz[aa]);
		do_type3(&par[bb], par[bb]);
		do_type3(&cnt[aa], cnt[aa]);
		par[bb] = aa, sz[aa] += sz[bb], cnt[aa] += cnt[bb];
		for(auto i : v[bb]) {
			do_type1(i, bb, aa);
		}
		v[bb].clear();
		return ops - ini;
	}
	void undo() {
		int cur = st.back();
		st.pop_back(), ops --;
		if(cur == 1) {
			int num; pii p;
			tie(num, p) = a.back(); a.pop_back();
			if(!ans[num]) {
				v[p.first].push_back(num);
				v[p.second].pop_back();
			}
		}
		else if(cur == 2) {
			pii p = b.back(); b.pop_back();
			if(p.first == 1) {
				if(s.find(p.second) != s.end())
					s.erase(s.find(p.second));
			}
			else s.insert(p.second);
		}
		else {
			pair<int*, int> p = c.back();
			c.pop_back();
			*p.first = p.second;
		}
	}
	void solve(int L, int R, vector<pii> del) {
		int cnt = ops, mid = (L + R) / 2, nd = get(L, R);
		vector<pii> l, r;
		for(auto i : del) {
			if(i.first <= mid) l.push_back(i);
			else r.push_back(i);
		}
		del.clear();
		for(auto i : evt[nd]) unite(i.first, i.second);
		if(L == R) {
			for(auto i : l) change(i.second, -1);
			for(auto i : s) if(v[i].size()) {
				for(auto j : v[i]) ans[j] = L;
				v[i].clear();
			}
		}
		else {
			int cur = ops;
			for(auto i : l) change(i.second, -1);
			solve(mid + 1, R, r);
			while(ops != cur) undo();
			solve(L, mid, l);
		}
		while(ops != cnt) undo();
	}
	void parse() {
		map<int, int> mp;
		int cur = 0;
		vector<pii> del, roads;
		rep(i, 1, q) {
			char c; cin >> c;
			if(c == 'A') {
				int x, y;
				cin >> x >> y;
				mp[++cur] = i;
				roads.push_back({x, y});
			}
			else if(c == 'D') {
				int x; cin >> x;
				del.push_back({i, x});
			}
			else {
				int x; cin >> x;
				int pre = mp[x];
				pii p = roads[x - 1];
				modify(1, q, pre, i - 1, p);
				mp.erase(mp.find(x));
			}
		}
		solve(1, q, del);
		rep(i, 1, n) cout << ans[i] << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n, q);
	parse();
	return 0;
}


