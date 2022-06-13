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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> mp(n + 1, vector<int>());
	vector<int> deg(n + 1, 0);
	priority_queue<int> pq;
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		mp[b].push_back(a);
		deg[a] ++;
	}
	rep(i, 1, n) if(!deg[i]) pq.push(i);
	vector<int> ans;
	while(pq.size()) {
		int cur = pq.top();
		pq.pop();
		ans.push_back(cur);
		for(auto i : mp[cur]) {
			if(!--deg[i]) pq.push(i);
		}
	}
	reverse(all(ans));
	rep(i, 0, n - 1) cout << ans[i] << " \n"[i == n - 1];
	return 0;
}


