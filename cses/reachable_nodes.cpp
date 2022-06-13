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
namespace solver {
	const int P = 50001;
	int n, m, ii, timestamp, sccid;
	vector<vector<int>> mp1, mp2;
	vector<int> pre, scc, D, L, instack;
	vector<bitset<P>> a;
	void init_(int _n, int _m) {
		n = _n, m = _m, ii = 0;
		timestamp = 0, sccid = 0;
		mp1.assign(n + 1, vector<int>());
		mp2.assign(n + 1, vector<int>());
		a.assign(n + 1, bitset<P>());
		instack.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		scc.assign(n + 1, 0);
		D.assign(n + 1, 0);
		L.assign(n + 1, 0);
	}
	void dfs(int x) {
		pre[ii++] = x, instack[x] = 1;
		D[x] = L[x] = ++timestamp;
		for(auto i : mp1[x]) {
			if(!D[i]) dfs(i), L[x] = min(L[i], L[x]);
			else if(instack[i]) L[x] = min(L[x], D[i]);
		}
		if(L[x] == D[x]) {
			sccid ++;
			while(pre[ii] != x) {
				ii--;
				instack[pre[ii]] = 0;
				scc[pre[ii]] = sccid;
			}
		}
	}
	void dp(int x) {
		D[x] = -1, a[x][x] = 1;
		for(auto i : mp2[x]) {
			if(D[i] != -1) dp(i);
			a[x] = a[x] | a[i];
		}
	}
	void solve() {
		rep(i, 1, n) if(!D[i]) dfs(i);
		rep(i, 1, n) for(auto j : mp1[i]) {
			if(scc[i] != scc[j]) mp2[scc[i]].push_back(scc[j]);
		}
		rep(i, 1, sccid) if(D[i] != -1) dp(i);
		rep(i, 1, m) {
			int x, y;
			cin >> x >> y;
			if(scc[x] == scc[y]) cout << "YES\n";
			else cout << (a[scc[x]][scc[y]] ? "YES\n" : "NO\n");
		}
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	init_(n, q);
	rep(i, 1, m) {
		int a, b;
		cin >> a >> b;
		mp1[a].push_back(b);
	}
	solve();

	return 0;
}


