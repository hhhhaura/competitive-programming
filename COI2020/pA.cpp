#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define int long long int 
#define pii pair<int, int>
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout(){cerr<< endl;}
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, m, tot, ii;
	const int P = 300;
	vector<int> dirx = {1, 0, 0, -1};
	vector<int> diry = {0, 1, -1, 0};
	vector<map<int, vector<int>>> v;
	vector<vector<int>> big, pix, mp;
	vector<int> par, yes, col, rk, vis;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		tot = n * m;
		v.assign(tot, map<int, vector<int>>());
		mp.assign(n, vector<int>(m, 0));
		big.assign(tot, vector<int>());
		pix.assign(tot, vector<int>());
		vis.assign(tot, 0);
		par.assign(tot, 0);
		yes.assign(tot, 0);
		col.assign(tot, 0);
		rk.assign(tot, 0);
	}
	int pos(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = pos(par[x]);
	}
	void traverse(int id, function<void(int)> operate) {
		id = pos(id), ii++;
		for(auto i : pix[id]) {
			int x = i / m, y = i % m;
			rep(j, 0, 3) {
				int nx = x + dirx[j], ny = y + diry[j];
				if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				int val = nx * m + ny;
				val = pos(val);
				if(val!= id && vis[val] != ii) {
					operate(val);
					vis[val] = ii;
				}
			}
		}
	}
	void golarge(int id, function<void(int)> operate) {
		id = pos(id);
		vis[id] = ++ii;
		for(auto i : big[id]) {
			int cur = pos(i);
			if(vis[cur] != ii) {
				operate(cur);
				vis[cur] = ii;
			}
		}
	}
	vector<int> nearbycolor(int id, int color) {
		id = pos(id);
		vector<int> ans;
		if(yes[id]) {
			vis[id] = ++ ii;
			if(v[id].find(color) != v[id].end()) {
				for(auto i : v[id][color]) {
					int val = pos(i);
					if(vis[val] != ii) {
						vis[val] = ii;
						if(col[val] == color)
							ans.push_back(val);
					}
				}
			}
			v[id][color].clear();
		}
		else {
			traverse(id, [&](int x) {
				if(col[x] == color) ans.push_back(x);
			});
		}
		return ans;
	}
	void belarge(int id) {
		id = pos(id);
		yes[id] = 1;
		traverse(id, [&](int x) {
			v[id][col[x]].push_back(x);
			big[x].push_back(id);
		});
	}
	void unite(int a, int b) {
		int aa = pos(a), bb = pos(b);
		if(aa == bb) return;
		if(rk[aa] < rk[bb]) swap(aa, bb);
		rk[aa] += (rk[aa] == rk[bb]);
		par[bb] = aa;
		if(yes[aa] && !yes[bb]) belarge(bb);
		if(yes[bb] && !yes[aa]) belarge(aa);
		// pixels
		if(pix[aa].size() < pix[bb].size()) pix[aa].swap(pix[bb]);
		for(auto i : pix[bb]) pix[aa].push_back(i);
		pix[bb].clear();
		// big
		for(auto i : big[bb]) big[aa].push_back(i);
		big[bb].clear();
		vector<int> tp;
		golarge(aa, [&](int x) {
			tp.push_back(x);
		});
		big[aa] = tp;
		//bycolor
		for(auto i : v[bb]) {
			if(v[aa][i.x].size() < i.y.size()) 
				v[aa][i.x].swap(i.y);
			auto &cur = v[aa][i.x];
			for(auto j : i.y) cur.push_back(j);
		}
		v[bb].clear();
		if(pix[aa].size() > P && !yes[aa]) belarge(aa);
		return;
	}
	void fill(int id, int color) {
		vector<int> tp = nearbycolor(id, color);
		for(auto i : tp) unite(i, id);
		col[pos(id)] = color;
		golarge(id, [&](int x) { 
			v[x][color].push_back(id);
		});
	}
	void solve() {
		rep(i, 0, n - 1) rep(j, 0, m - 1) {
			int val = i * m + j;
			par[val] = val;
			col[val] = mp[i][j];
			pix[val].push_back(val);
		}
		rep(i, 0, n - 1) rep(j, 0, m - 1) {
			int val = i * m + j;
			fill(val, mp[i][j]);
		}
		int q; cin >> q;
		while(q--) {
			int x, y, to;
			cin >> x >> y >> to;
			x -= 1;
			y -= 1;
			fill(x * m + y, to);
		
		}
		rep(i, 0, n - 1) rep(j, 0, m - 1) 
			cout << col[pos(i * m + j)] << " \n"[j + 1 == m];
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 0, n - 1) rep(j, 0, m - 1)
		cin >> mp[i][j];
	solve();
	return 0;
}


