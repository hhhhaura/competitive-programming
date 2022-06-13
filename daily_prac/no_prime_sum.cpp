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
	int n, m, ii = 0;
	const int P = 200000;
	vector<int> fac, p;
	vector<int> x, y, visx, visy, match;
	vector<vector<int>> mp;
	int dfs1(int x) {
		for(auto i : mp[x]) if(visy[i] != ii) {
			visy[i] = ii;
			if(match[i] == -1 || dfs1(match[i])) {
				match[i] = x;
				visx[x] = 1;
				return 1;
			}
		}
		return 0;
	}
	void dfs2(int x) {
		visx[x] = ii;
		for(auto i : mp[x]) if(visy[i] != ii) {
			visy[i] = ii;
			dfs2(match[i]);
		}
	}
	void solve() {
		fac.assign(P + 1, 1);
		rep(i, 2, P) {
			if(fac[i] == 1) p.push_back(i);
			for(auto j : p) {
				if(i * j > P) break;
				fac[i * j] = j;
				if(i % j == 0) break;
			}
		}
		sort(all(x)), x.resize(unique(all(x)) - x.begin());
		sort(all(y)), y.resize(unique(all(y)) - y.begin());
		n = x.size();
		m = y.size();
		visx.assign(n, 0);
		visy.assign(m, 0);
		match.assign(m, -1);
		mp.assign(n, vector<int>());
		rep(i, 0, n - 1) rep(j, 0, m - 1) {
			if(fac[x[i] + y[j]] == 1) 
				mp[i].push_back(j);
		}
		int ans = 0;
		rep(i, 0, n - 1) ii++, ans += dfs1(i);
		ii++;
		rep(i, 0, n - 1) if(!visx[i]) dfs2(i);
		cout << ans << "\n";
		vector<int> tot;
		rep(i, 0, n - 1) if(visx[i] != ii) tot.push_back(x[i]);
		rep(i, 0, m - 1) if(visy[i] == ii) tot.push_back(y[i]);
		rep(i, 0, ans - 1) cout << tot[i] << " \n"[i + 1 == ans];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	rep(i, 1, n) {
		int val; cin >> val;
		if(val & 1) x.push_back(val);
		else y.push_back(val);
	}
	solve();
	return 0;
}


