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
	int n, timestamp, yes;
	vector<vector<int>> mp;
	vector<int> L, D;
	vector<pii> ans;
	void init_(int _n) {
		n = _n, timestamp = 0;
		yes = 1;
		mp.assign(n + 1, vector<int>());
		D.assign(n + 1, 0);
		L.assign(n + 1, 0);
		ans.clear();
	}
	void dfs(int x, int par) {
		D[x] = L[x] = ++timestamp;
		for(auto i : mp[x]) if(i != par) {
			if(D[i] < D[x]) ans.push_back({x, i});
			if(!D[i]) dfs(i, x);
			if(L[i] > D[x]) yes = 0;
			L[x] = min(L[x], L[i]);
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
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	dfs(1, 1);
	if(!yes || timestamp < n) cout << "IMPOSSIBLE\n";
	else for(auto i : ans) cout << i.x << " " << i.y << "\n";
	return 0;
}


