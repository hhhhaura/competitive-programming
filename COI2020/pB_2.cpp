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
namespace solver {
	int n;
	vector<vector<int>> mp, mp1;
	vector<int> dep, dis, a, v, vis, par;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		mp1.assign(n + 1, vector<int>());
		dep.assign(n + 1, 0);
		dis.assign(n + 1, INF);
		vis.assign(n + 1, 0);
		par.assign(n + 1, 0);
		a.assign(n + 1, 0);
		v.assign(n, 0);
		iota(all(v), 1);
	}
	void dfs(int x, int p, int d) {
		par[x] = p, dep[x] = d;
		for(auto i : mp[x]) if(i != p) dfs(i, x, d + 1);
	}
	void dfs1(int x) {
		vis[x] = 1;
		for(auto i : mp1[x]) 
			if(!vis[i]) dfs1(i);
	}
	void solve() {
		queue<int> q;
		rep(i, 1, n) if(a[i]) {
			q.push(i);
			dis[i] = 0;
		}
		while(q.size()) {
			int cur = q.front();
			q.pop();
			for(auto i : mp[cur]) {
				if(dis[i] == INF) {
					dis[i] = dis[cur] + 1;
					q.push(i);
				}
			}
		}
		rep(i, 1, n) for(auto j : mp[i]) 
			if(dis[j] + 1 == dis[i]) mp1[i].push_back(j);
		vector<int> ans;
		dfs(1, 1, 0);
		sort(all(v), [&](int a, int b) {
			return dep[a] > dep[b];
		});
		for(auto i : v) if(!vis[i] && a[i]) {
			int cur = i;
			while(cur != 1 && dis[par[cur]] 
				>= dep[i] - dep[par[cur]]) cur = par[cur];
			assert(!vis[cur]);
			dfs1(cur);
			ans.push_back(cur);
		}
		cout << ans.size() << "\n";
		rep(i, 0, signed(ans.size()) - 1)
			cout << ans[i] << " \n"[i + 1 == ans.size()];
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	rep(i, 1, k) {
		int x; cin >> x;
		a[x] = 1;
	}
	solve();
	return 0;
}


