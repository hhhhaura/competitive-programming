#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()

using namespace std;

#define INF 1000000000
#define MOD 1000000007
#define eps (1e-9)
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
	int n, m, timestamp, bad, ans;
	vector<int> x, y, vis, es, yes, L, D, ap;
	vector<vector<int>> mp, mp1;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		vis.clear();
		es.clear();
		ap.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
		mp1.assign(n + 1, vector<int>());
	}
	void add_edge(int a, int b) {
		mp[a].push_back(es.size());
		mp[b].push_back(es.size());
		es.push_back(a ^ b);
		vis.push_back(0);
	}
	void dfs(int x, int par, bool yes) {
		int ch = 0, isap = 0;
		L[x] = D[x] = ++ timestamp;
		for(auto i : mp1[x]) if(i != par) {
			if(i == bad) continue;
			if(!D[i]) {
				ch ++, dfs(i, x, yes);
				L[x] = min(L[x], L[i]);
				if(L[i] >= D[x]) isap = 1;
			}
			else L[x] = min(L[x], D[i]);
		}
		if(x == par && ch < 2) isap = 0;
		if(isap) ans ++;
		if(yes) ap[x] = isap;
	}
	void bfs(int st) {
		queue<int> q;
		yes[st] = 0;
		q.push(st);
		while(q.size()) {
			int cur = q.front();
			q.pop();
			for(auto i : mp[cur]) {
				int to = es[i] ^ cur;
				if(yes[to] == INF) {
					vis[i] = 1;
					yes[to] = yes[cur] + 1;
					q.push(to);
				}
			}
		}
		return;
	}
	int dfs2(int x) {
		int ans = 1;
		D[x] = 1;
		for(auto i : mp1[x]) {
			if(!D[i]) ans += dfs2(i);
		}
		return ans;
	}
	void solve() {
		rep(t, 1, 3) {
			yes.assign(n + 1, INF);
			rep(i, 1, n) if(yes[i] == INF) bfs(i);
			rep(i, 1, n) for(auto j : mp[i]) {
				int to = es[j] ^ i;
				if(vis[j] && yes[i] + 1 == yes[to]) {
					mp1[i].push_back(to);
					mp1[to].push_back(i);
				}
			}
			vector<vector<int>> tp(n + 1, vector<int>());
			rep(i, 1, n) for(auto j : mp[i]) if(!vis[j]) {
				tp[i].push_back(j);
			}
			mp = tp;
		}
		bad = 0, timestamp = 0;
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		dfs(1, 1, 1);
		int cnt = 0;
		rep(i, 1, n) if(!ap[i]) {
			L.assign(n + 1, 0);
			D.assign(n + 1, 0);
			bad = i, ans = 0;
			int top = (i == 1 ? 2 : 1);
			dfs(top, top, 0);
			cnt += ans;
		}
		rep(i, 1, n) if(ap[i]) {
			D.assign(n + 1, 0);
			D[i] = 1;
			int tot = 0, mn = 0;
			for(auto j : mp1[i]) if(!D[j]) {
				tot ++;
				int cur = dfs2(j);
				mn += (cur == 1);
			}
			if(tot > 2) cnt += n - 1;
			else cnt += n - 1 - mn;
		}
		cout << cnt / 2 << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	solve();
	return 0;
}


