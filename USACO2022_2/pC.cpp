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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	const int k = 100000000;
	vector<vector<pii>> mp(n + 1, vector<pii>());
	vector<int> dis(n + 1, 0);
	rep(i, 1, n) {
		int x; cin >> x;
		mp[i].push_back({x, k});
		if(x != n) mp[x + 1].push_back({i, -1-k});
		if(i != 1) mp[i].push_back({i - 1, 0});
	}
	queue<int> q; 
	rep(i, 1, n) q.push(i);
	while(q.size()) {
		int cur = q.front(); q.pop();
		for(auto i : mp[cur]) {
			int v = i.second + dis[cur];
			if(v < dis[i.first]) {
				dis[i.first] = v;
				q.push(i.first);
			}
		}
	}
	cout << k << "\n";
	int ans = 0;
	rep(i, 1, n) ans = min(ans, dis[i]);
	rep(i, 1, n) cout << dis[i] - ans << "\n";
	return 0;
}


