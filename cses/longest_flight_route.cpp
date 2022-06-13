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
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count)
 
#ifdef wiwihorz
#define print(a...) cerr << "Line " << __LINE__, kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, m;
vector<int> vis, pre, mx;
vector<vector<int>> mp;
void dfs(int x) {
	vis[x] = 1;
	if(x == n) mx[x] = 1;
	for(auto i : mp[x]) {
		if(!vis[i]) dfs(i);
		if(mx[i] + 1 > mx[x]) {
			pre[x] = i;
			mx[x] = mx[i] + 1;
		}
	}
}
 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	mp.assign(n + 1, vector<int>());
	pre.assign(n + 1, 0);
	mx.assign(n + 1, -INF);
	vis.assign(n + 1, 0);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
	}
	dfs(1);
	if(!vis[n]) cout << "IMPOSSIBLE\n";
	else {
		cout << mx[1] << "\n";
		int cur = 1;
		rep(i, 1, mx[1]) {
			cout << cur << " \n"[i == mx[1]];
			cur = pre[cur];
		}
	}
	return 0;
}
