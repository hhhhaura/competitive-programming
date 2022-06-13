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
	int n, timestamp;
	vector<vector<int>> mp;
	vector<int> L, D, x, y, es, ap, bri;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
	}
	void add_edge(int a, int b) {
		timestamp = 0;
		mp[a].push_back(es.size());
		mp[b].push_back(es.size());
		es.push_back(a ^ b);
		x.push_back(a);
		y.push_back(b);
	}
	void dfs(int x, int par) {
		L[x] = D[x] = ++ timestamp;
		int ch = 0, isap = 0;
		for(auto i : mp[x]) if(i != par) {
			int to = es[i] ^ x;
			if(!D[to]) {
				ch ++, dfs(to, i);
				isap |= (L[to] >= D[x]);
				L[x] = min(L[x], L[to]);
				if(L[to] > D[x]) bri.push_back(i);
			}
			else L[x] = min(L[x], D[to]);
		}

		if(par == -1 && ch < 2) isap = 0;
		if(isap) ap.push_back(x);
	}
	void solve() {
		rep(i, 1, n) if(!D[i]) dfs(i, -1);
		cout << ap.size() << "\n";
		rep(i, 0, signed(ap.size()) - 1) 
			cout << ap[i] << " \n"[i + 1 == ap.size()];

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
		add_edge(a, b);
	}
	solve();
	return 0;
}


