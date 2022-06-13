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
namespace solver {
	int n;
	struct edge { int to, cap, rev, yes; };
	vector<vector<edge>> mp;
	vector<int> iter, dis, ans;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<edge>());
	}
	void add_edge(int a, int b, int c) {
		mp[a].push_back({b, c, mp[b].size(), 1});
		mp[b].push_back({a, 0, signed(mp[a].size()) - 1, 0});
	}
	bool bfs() {
		iter.assign(n + 1, 0);
		dis.assign(n + 1, INF);
		dis[1] = 0;
		queue<int> q;
		q.push(1);
		while(q.size()) {
			int cur = q.front();
			q.pop();
			for(auto i : mp[cur]) if(i.cap) {
				if(dis[i.to] != INF) continue;
				dis[i.to] = dis[cur] + 1;
				q.push(i.to);
			}
		}
		return dis[n] != INF;
	}
	int dfs(int x, int flow) {
		if(x == n) return flow;
		for(int &i = iter[x]; i < mp[x].size(); i ++) {
			edge &e = mp[x][i];
			if(e.cap && dis[e.to] == dis[x] + 1) {
				int cur = dfs(e.to, min(flow, e.cap));
				if(cur) {
					mp[e.to][e.rev].cap += cur;
					e.cap -= cur;
					return cur;
				}
			}
		}
		return 0;
	}
	int flow() {
		int ans = 0;
		while(bfs()) {
			int cur = 0;
			while(cur = dfs(1, INF), cur) ans += cur;
		}
		return ans;
	}
	void traverse(int x) {
		ans.push_back(x);
		while(iter[x] < mp[x].size()) {
			edge e = mp[x][iter[x]++];
			if(!e.yes || e.cap) continue;
			traverse(e.to);
			return;
		}
	}
	void solve() {
		int tot = flow();
		print(tot);
		cout << tot << "\n";
		iter.assign(n + 1, 0);
		while(iter[1] < mp[1].size()) {
			ans.clear();
			traverse(1);
			cout << ans.size() << "\n";
			rep(i, 0, signed(ans.size()) - 1) cout << ans[i] 
				<< " \n"[i + 1 == ans.size()];
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b, 1);
	}
	solve();
	return 0;
}


