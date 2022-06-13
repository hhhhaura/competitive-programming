#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
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
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n = 50, m = 2000, root;
	vector<int> es, piv, deg, vis;
	vector<vector<int>> mp;
	vector<int> ans;
	void init_() {
		ans.clear();
		vis.assign(m + 1, 0);
		piv.assign(n + 1, 0);
		deg.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
		es.assign(m + 1, 0);
	}
	void add_edge(int a, int b, int c) {
		es[c] = a ^ b;
		deg[a] ++, deg[b] ++;
		mp[a].push_back(c);
		mp[b].push_back(c);
	}
	void dfs(int x) {
		while(piv[x] < mp[x].size()) {
			int id = mp[x][piv[x]++];
			int to = es[id] ^ x;
			if(vis[id]) continue;
			vis[id] = 1;
			dfs(to);
			ans.push_back(id);
		}	
	}
	void solve() {
		rep(i, 1, n) sort(all(mp[i]));
		int bad = 0;
		rep(i, 1, n) if(deg[i] & 1) bad = 1;
		if(bad) {
			cout << "Round trip does not exist.\n";
			return;
		}
		dfs(root);
		reverse(all(ans));
		rep(i, 0, signed(ans.size()) - 1)
			cout << ans[i] << " \n"[i + 1 == ans.size()];
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int a, b, c;
	while(cin >> a >> b && a && b) {
		cin >> c;
		init_();
		add_edge(a, b, c);
		root = min(a, b);
		while(cin >> a >> b && a && b) {
			cin >> c;
			add_edge(a, b, c);
		}
		solve();
		cout << endl;
	} 
	return 0;
}

