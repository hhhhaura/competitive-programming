#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define int long long int 
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
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
	const int bk = 600;
	vector<vector<int>> mp;
	vector<int> par, sz, rk, yes, val;
	vector<map<int, vector<int>>> col;
	vector<vector<int>> v, big;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		tot = n * m, ii = 0;
		mp.assign(n, vector<int>(m, 0));
		par.assign(tot, 0);
		yes.assign(tot, 0);
		iota(all(par), 0);
		sz.assign(tot, 1);
		rk.assign(tot, 0);
		val.assign(tot, 0);
		big.assign(tot, vector<int>());
		v.assign(tot, vector<int>());
		col.assign(tot, map<int, vector<int>>());
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void to_big(int cur) {
		for(auto i : v[cur]) {
			if(find_par(i) == cur) continue;
			int num = val[find_par(i)];
			if(col[cur].find(num) == col[cur].end()) 
				col[cur][num] = vector<int>();
			col[cur][num].push_back(i);
			if(!yes[cur]) big[find_par(i)].push_back(cur);
		}
		yes[cur] = 1;
		v[cur].clear();
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[bb] > rk[aa]) swap(aa, bb);
		rk[aa] += (rk[aa] == rk[bb]);
		sz[aa] += sz[bb];
		par[bb] = aa;
		if(sz[aa] < sz[bb]) {
			col[aa].swap(col[bb]);
			v[aa].swap(v[bb]);
			big[aa].swap(big[bb]);
		}
		for(auto i : col[bb]) {
			if(col[aa].find(i.x) != col[aa].end()) 
				for(auto j : i.y) col[aa][i.x].push_back(j);
			else col[aa][i.x] = i.y;
		}
		col[bb].clear();
		for(auto i : v[bb]) v[aa].push_back(i);
		v[bb].clear();
		for(auto i : big[bb]) big[aa].push_back(i);
		big[bb].clear();
		if(sz[aa] >= bk) to_big(aa);
	}
	void solve() {
		vector<int> dirx = {1, 0, 0, -1};
		vector<int> diry = {0, 1, -1, 0};
		rep(i, 0, n - 1) rep(j, 0, m - 1) {
			int cur = i * m + j;
			rep(k, 0, 3) {
				int nx = dirx[k] + i;
				int ny = diry[k] + j;
				if(nx < 0 || nx >= n) continue;
				if(ny < 0 || ny >= m) continue;
				v[cur].push_back(nx * m + ny);
			}
			val[cur] = mp[i][j];
		}
		rep(i, 0, n - 1) rep(j, 0, m - 1) {
			int cur = i * m + j;
			rep(k, 0, 3) {
				int nx = dirx[k] + i;
				int ny = diry[k] + j;
				if(nx < 0 || nx >= n) continue;
				if(ny < 0 || ny >= m) continue;
				if(mp[i][j] == mp[nx][ny]) unite(cur, nx * m + ny);
			}
		}
		int q; cin >> q;
		while(q--) {
			int x, y, num;
			cin >> x >> y >> num;
			x --, y --;
			int cur = find_par(x * m + y);
			vector<int> to;
			if(!yes[cur]) for(auto i : v[cur]) 
				if(val[find_par(i)] == num) to.push_back(i);
			else if(col[cur].find(num) != col[cur].end()) {
				for(auto i : col[cur][num]) if(val[find_par(i)] == num) 
					to.push_back(i);
				col[cur].erase(col[cur].find(num));
			}
			val[cur] = num;
			for(auto i : to) unite(i, cur);
			cur = find_par(cur);
			for(auto i : big[cur]) {
				if(find_par(i) == cur) continue;
				int tp = find_par(i);
				if(col[tp].find(num) == col[tp].end()) 
					col[tp][num] = vector<int>();
				col[tp][num].push_back(cur);
			}
		}
		rep(i, 0, n - 1) rep(j, 0, m - 1) 
			cout << val[find_par(i * m + j)] << " \n"[j + 1 == m];

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


