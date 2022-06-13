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
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pii>> mp(n + 1, vector<pii>());
	vector<priority_queue<int>> dis(n + 1, priority_queue<int>());
	rep(i, 1, m) {
		int a, b, c;
		cin >> a >> b >> c;
		mp[a].push_back({b, c});
	}
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, 1});
	dis[1].push(0);
	while(pq.size()) {
		pii p = pq.top(); pq.pop();
		if(p.x > dis[p.y].top()) continue;
		int cur = p.y;
		for(auto i : mp[cur]) {
			int val = i.y + p.x;
			if(dis[i.x].size() < k) {
				dis[i.x].push(val);
				pq.push({val, i.x});
			}
			else if(dis[i.x].top() > val) {
				dis[i.x].push(val);
				dis[i.x].pop();
				pq.push({val, i.x});
			}
		}
	}
	assert(dis[n].size() == k);
	vector<int> ans(k + 1, 0);
	rrep(i, 1, k) {
		ans[i] = dis[n].top();
		dis[n].pop();
	}
	rep(i, 1, k) cout << ans[i] << " \n"[i == k];
	return 0;
}


