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
namespace solver {
	int n;
	vector<vector<int>> mp;
	vector<int> sz, mx;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) if(i != par) {
			get_sz(i, x);
			sz[x] += sz[i];
			mx[x] = max(mx[x], sz[i]);
		}
	}
	int get_cen(int x, int par) {
		int best = x;
		for(auto i : mp[x]) if(i != par) {
			int cur = get_cen(i, x);
			if(max(mx[cur], n - sz[cur]) <
				max(mx[best], n - sz[best])) best = cur;
		}
		return best;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	get_sz(1, 1);
	cout << get_cen(1, 1) << "\n";
	return 0;
}


