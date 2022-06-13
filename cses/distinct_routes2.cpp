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
	int n, k, s, t;
	struct edge { int to, cap, cost, rev, yes; };
	vector<vector<edge>> mp;
	vector<int> dis, piv, ans;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		s = n + 1, t = n + 2;
		mp.assign(n + 3, vector<edge>());
		dis.assign(n + 3, INF);
		piv.assign(n + 3, 0);
	}
	void add_edge(int a, int b, int cap, int cost) {
		mp[a].push_back({b, cap, cost, signed(mp[b].size()), 1});
		mp[b].push_back({a, 0, -cost, signed(mp[a].size()) - 1, 0});
	}
	bool dijkstra() {
		dis.assign(n + 3, INF);
		piv.assign(n + 3, 0);
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		dis[s] = 0, pq.push({0, s});
		while(pq.size()) {
			pii p = pq.top(); pq.pop();
			if(p.x != dis[p.y]) continue;
			int cur = p.y;
			for(auto i : mp[cur]) if(i.cap) {
				int v = dis[cur] + i.cost;
				if(v < dis[i.to]) {
					dis[i.to] = v;
					pq.push({v, i.to});
				}
			}
		}
		print(dis[t]);
		return dis[t] != INF;
	}
	int dfs(int x, int flow) {
		if(x == t || !flow) return flow;
		print(x, flow, piv[x], mp[x].size());
		for(int &i = piv[x]; i < mp[x].size(); i ++) {
			edge &e = mp[x][i];
			if(e.cap && dis[x] + e.cost == dis[e.to]) {
			print(e.to, dis[x], e.cost, dis[e.to], e.cap);;
				int cur = dfs(e.to, min(flow, e.cap));
				print(cur);
				if(cur) {

					e.cap -= cur;
					mp[e.to][e.rev].cap += cur;
					return cur;
				}
			}
		}
		return 0;
	}
	void traverse(int x) {
		ans.push_back(x);
		if(x == n) return;
		while(piv[x] < mp[x].size()) {
			edge e = mp[x][piv[x]++];
			if(!e.yes || e.cap) continue;
			traverse(e.to);
			return;
		}
	}
	void solve() {
		add_edge(n + 1, 1, k, 1);
		add_edge(n, n + 2, k, 1);
		int tot = 0, cost = 0;
		while(dijkstra()) {
			int cur = 0, val = 0;
			
			while(cur = dfs(s, INF), cur) print(cur), val += cur;
			print(val);
			val -= 2;
			cost += val * dis[t];
			tot += val;
		}
		if(tot < k) cout << "-1\n";
		else {
			cout << cost << "\n";
			rep(i, 1, k) {
				ans.clear();
				traverse(1);
				cout << ans.size() << "\n";
				rep(j, 0, signed(ans.size()) - 1)
					cout << ans[j] << " \n"[j + 1 == ans.size()];
			}
		}
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	init_(n, k);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b, 1, 1);
	}
	solve();
	return 0;
}


