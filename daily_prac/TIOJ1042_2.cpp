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
struct KM {
	int n, ii;
	vector<vector<int>> mp;
	vector<int> vx, vy, lx, ly, match, slack;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>(n + 1, 0));
		vx.assign(n + 1, 0);
		vy.assign(n + 1, 0);
		lx.assign(n + 1, 0);
		ly.assign(n + 1, 0);
		match.assign(n + 1, -1);
		slack.assign(n + 1, INF);
	}
	bool dfs(int x, int yes) {
		if(vx[x] == ii) return 0;
		vx[x] = ii;
		rep(i, 1, n) if(vy[i] != ii) {
			int val = lx[x] + ly[i] - mp[x][i];
			if(val == 0) {
				vy[i] = ii;
				if(match[i] == -1 || dfs(match[i], yes)) {
					if(yes) match[i] = x;
					return 1;
				}
			}
			else slack[i] = min(slack[i], val);
		}
		return 0;
	}
	bool augment() {
		rep(i, 1, n) if(vy[i] != ii && slack[i] == 0) {
			if(match[i] == -1 || dfs(match[i], 0)) return 1;
		}
		return 0;
	}
	void relabel() {
		int val = INF;
		rep(i, 1, n) if(vy[i] != ii) val = min(val, slack[i]);
		rep(i, 1, n) if(vx[i] == ii) lx[i] -= val;
		rep(i, 1, n) if(vy[i] == ii) ly[i] += val;
		rep(i, 1, n) if(vy[i] != ii) slack[i] -= val;
	}
	int solve() {
		rep(i, 1, n) rep(j, 1, n) 
			lx[i] = max(lx[i], mp[i][j]);
		rep(i, 1, n) {
			ii ++;
			rep(j, 1, n) slack[j] = INF;
			if(dfs(i, 1)) continue;
			while(!augment()) relabel();
			ii++;
			assert(dfs(i, 1));
		}
		int ans = 0;
		rep(i, 1, n) ans += mp[match[i]][i];
		return ans;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	while(cin >> n && n) {
		KM km; km.init_(n);
		rep(i, 1, n) rep(j, 1, n) {
			int x; cin >> x;
			x = max(0ll, x);
			km.mp[i][j] = x;
		}
		cout << km.solve() << "\n";
	}
	return 0;
}


