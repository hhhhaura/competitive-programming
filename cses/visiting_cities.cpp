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
	int n;
	pii MOD = {2147483647, 1000000009};
	vector<vector<pii>> mp1, mp2;
	vector<int> d1, d2;
	vector<pii> cnt1, cnt2;
	void init_(int _n) {
		n = _n;
		mp1.assign(n + 1, vector<pii>());
		mp2.assign(n + 1, vector<pii>());
		d1.assign(n + 1, INF);
		d2.assign(n + 1, INF);
		cnt1.assign(n + 1, {0, 0});
		cnt2.assign(n + 1, {0, 0});
	}
	void dijkstra(vector<vector<pii>> &mp, 
		vector<int> &dis, vector<pii> &cnt, int s) {
		dis[s] = 0, cnt[s] = {1, 1};
		priority_queue<pii, vector<pii>, greater<pii>> q;
		q.push({0, s});
		while(q.size()) {
			pii p = q.top(); q.pop();
			if(p.x != dis[p.y]) continue;
			int cur = p.y;
			for(auto i : mp[cur]) {
				int val = dis[cur] + i.y;
				if(val < dis[i.x]) {
					dis[i.x] = val;
					cnt[i.x] = cnt[cur];
					q.push({val, i.x});
				}
				else if(val == dis[i.x]) {
					cnt[i.x].x = (cnt[i.x].x + cnt[cur].x) % MOD.x;
					cnt[i.x].y = (cnt[i.x].y + cnt[cur].y) % MOD.y;
				}
			}
		}
		return;
	}
	void solve() {
		dijkstra(mp1, d1, cnt1, 1);
		dijkstra(mp2, d2, cnt2, n);
		vector<int> ans;
		rep(i, 1, n) {
			int valx = cnt1[i].x * cnt2[i].x % MOD.x;
			int valy = cnt1[i].y * cnt2[i].y % MOD.y;
			if(d1[i] + d2[i] != d1[n]) continue;
			if(valx == cnt1[n].x &&
				valy == cnt1[n].y) ans.push_back(i);
		}
		cout << ans.size() << "\n";
		rep(i, 0, signed(ans.size()) - 1)
			cout << ans[i] << " \n"[i + 1 == ans.size()];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int a, b, c;
		cin >> a >> b >> c;
		mp1[a].push_back({b, c});
		mp2[b].push_back({a, c});
	}
	solve();
	return 0;
}


