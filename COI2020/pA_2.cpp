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
	const int K = 30;
	int n, r, c, m, ii;
	vector<int> dirx = {1, 0, -1, 0};
	vector<int> diry = {0, 1, 0, -1};
	vector<int> col, par, rk, sz, vis, yes;
	vector<vector<int>> mp;
	vector<set<pii>> v;
	vector<set<int>> big;
	void init_(int _r, int _c) {
		r = _r, c = _c, 
		ii = 0, n = r * c;
		yes.assign(n, 0);
		sz.assign(n, 0);
		col.assign(n, 0);
		par.assign(n, 0);
		iota(all(par), 0);
		rk.assign(n, 0);
		vis.assign(n, 0);
		mp.assign(r, vector<int>(c, 0));
		v.assign(n, set<pii>());
		big.assign(n, set<int>());
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void to_big(int st) {
		queue<int> q;
		st = find_par(st);
		yes[st] = 1;
		q.push(st), ii++;
		vis[st] = ii;
		while(q.size()) {
			int cur = q.front();
			q.pop();
			int x = cur / c, y = cur % c;
			rep(i, 0, 3) {
				int nx = dirx[i] + x;
				int ny = diry[i] + y;
				if(nx < 0 || nx >= r) continue;
				if(ny < 0 || ny >= c) continue;
				int to = nx * c + ny;
				int p = find_par(to);
				if(vis[to] == ii) continue;
				vis[to] = ii;
				if(p != st) {
					v[st].insert({col[p], p});
					big[p].insert(st);
				}
				else q.push(to);
			}
		}
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] < rk[bb]) swap(aa, bb);
		rk[aa] += (rk[aa] == rk[bb]);
		sz[aa] += sz[bb];
		par[bb] = aa;
		if(big[aa] < big[bb]) big[aa].swap(big[bb]);
		for(auto i : big[bb]) if(find_par(i) != aa) big[aa].insert(i);
		big[bb].clear();
		if(v[aa] < v[bb]) v[aa].swap(v[bb]);
		for(auto i : v[bb]) v[aa].insert(i);
		v[bb].clear();
		return;
	}
	vector<int> color(int st, int val) {
		vector<int> tot;
		st = find_par(st);
		if(sz[st] >= K) {
			auto it = v[st].lower_bound({val, -INF});
			while(it != v[st].end() && it -> x == val) {
				if(col[find_par(it -> y)] == val)
					tot.push_back(it -> y);
				auto tp = it;
				it = next(it);
				v[st].erase(it);
			}
		}
		else {
			queue<int> q;
			q.push(st), ii++;
			vis[st] = ii;
			while(q.size()) {
				int cur = q.front();
				q.pop();
				int x = cur / c, y = cur % c;
				rep(i, 0, 3) {
					int nx = dirx[i] + x;
					int ny = diry[i] + y;
					if(nx < 0 || nx >= r) continue;
					if(ny < 0 || ny >= c) continue;
					int to = nx * c + ny;
					int p = find_par(to);
					if(vis[to] == ii) continue;
					vis[to] = ii;
					if(p != st && col[p] == val) tot.push_back(p);
					else if(p == st) q.push(to);
				}
			}
		}
		return tot;
	}
	void solve() {
		rep(i, 0, r - 1) rep(j, 0, c - 1) {
			int cur = i * c + j;
			col[cur] = mp[i][j];
			rep(k, 0, 3) {
				int nx = dirx[k] + i;
				int ny = diry[k] + j;
				if(nx < 0 || nx >= r) continue;
				if(ny < 0 || ny >= c) continue;
				int to = nx * c + ny;
				if(mp[i][j] == mp[nx][ny]) unite(cur, to);
			}
			cur = find_par(cur);
			if(!yes[cur] && sz[cur] >= K) to_big(cur); 
		}
		cin >> m;
		while(m--) {
			int x, y, val;
			cin >> x >> y >> val;
			x --, y--;
			print(x, y, val);
			int cur = x * c + y;
			cur = find_par(cur);
			col[cur] = val;
			vector<int> tp = color(cur, val);
			print(x, y, val);
//			for(auto i : tp) {
//				int a = i / c, b = i % c;
//				print(a, b);
//			}
			for(auto i : tp) unite(i, cur);
			cur = find_par(cur);
			if(!yes[cur] && sz[cur] >= K) to_big(cur);
			for(auto i : big[cur]) if(find_par(i) != cur)
				v[find_par(i)].insert({val, cur});
		}
		rep(i, 0, r - 1) rep(j, 0, c - 1) 
			cout << col[find_par(i * c + j)] << " \n"[j + 1 == c];
		
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int r, c;
	cin >> r >> c;
	init_(r, c);
	rep(i, 0, r - 1) rep(j, 0, c - 1)
		cin >> mp[i][j];
	solve();
	return 0;
}


