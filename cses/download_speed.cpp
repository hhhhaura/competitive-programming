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
struct DINIC {
	int n, s, t;
	struct edge { int to, cap, rev;};
	vector<int> level, iter;
	vector<vector<edge>> mp;
	void init_(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		level.assign(n + 1, INF);
		iter.assign(n + 1, 0);
		mp.assign(n + 1, vector<edge>());
	}
	void add_edge(int a, int b, int c) {
		mp[a].push_back({b, c, signed(mp[b].size())});
		mp[b].push_back({a, 0, signed(mp[a].size()) - 1});
	}
	bool bfs() {
		level.assign(n + 1, INF);
		iter.assign(n + 1, 0);
		level[s] = 0;
		queue<int> q;
		q.push(s);
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) {
				if(!i.cap) continue;
				if(level[i.to] != INF) continue;
				level[i.to] = level[cur] + 1;
				q.push(i.to);
			} 
		}
		return level[t] != INF;
	}
	int dfs(int x, int val) {
		if(x == t) return val;
		for(int &i = iter[x]; i < mp[x].size(); i ++) {
			edge &e = mp[x][i];
			if(level[x] + 1 != level[e.to] || !e.cap) continue;
			int cur = dfs(e.to, min(val, e.cap));
			if(cur) {
				e.cap -= cur;
				mp[e.to][e.rev].cap += cur;
				return cur;
			}
		}
		return 0;
	}
	int flow() {
		int ans = 0;
		while(bfs()) {
			int cur = 0;
			while(cur = dfs(s, INF), cur) ans += cur;
		}
		return ans;
	}
	vector<int> min_cut() {
		vector<int> vis(n + 1, 0);
		queue<int> q;
		q.push(s);
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) if(i.cap) {
				if(vis[i.to]) continue;
				vis[i.to] = 1;
				q.push(i.to);
			}
		}
		return vis;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	DINIC ac;
	ac.init_(n, 1, n);
	rep(i, 1, m) {
		int a, b, c;
		cin >> a >> b >> c;
		ac.add_edge(a, b, c);
	}
	cout << ac.flow() << "\n";
	return 0;
}


