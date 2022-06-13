#define wiwihorz
#include "game.h"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define ll long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000
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
#define x first
#define y second
int n, k, ans, ii;
vector<vector<int>> mp, mp1;
vector<int> to, from;
vector<int> vis;
// special case : self loop
void init(int _n, int _k) {
	n = _n, k = _k, ans = 0, ii = 0;
	vis.assign(n, 0);
	mp.assign(n, vector<int>());
	mp1.assign(n, vector<int>());
	to.assign(n, INF);
	from.assign(n, -1);
	rep(i, 0, k - 2) {
		mp[i].push_back(i + 1);
		mp1[i + 1].push_back(i);
	}
	rep(i, 0, k - 1) from[i] = to[i] = i;
}
void dfs(int x, int tp, int pos) {
	if(ans) return;
	if(tp == 1) {
		if(to[x] <= pos) return;
		to[x] = pos;
		for(auto i : mp1[x]) if(vis[i] != ii) {
			if(ans) return;
			dfs(i, tp, pos);
		}
	}
	else {
		if(from[x] >= pos) return;
		from[x] = pos;
		for(auto i : mp[x]) if(vis[i] != ii) {
			if(ans) return;
			dfs(i, tp, pos);
		}
	}
	if(!(from[x] == to[x] && to[x] == x) && from[x] >= to[x]) {
		ans = 1;
		return;
	}
}
int add_teleporter(int u, int v) {
	// u to v
	if(ans || (u == v && u < k)) return 1;
	mp[u].push_back(v);
	mp1[v].push_back(u);
	if(from[u] > from[v]) ii++, dfs(v, 0, from[u]);
	if(to[v] < to[u]) ii++, dfs(u, 1, to[v]);
	if(ans) return 1;
	else return 0;
}

