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
	vector<int> slk, lx, ly, vx, vy, mx, my;
	void init_(int _n) {
		n = _n, ii = 0;
		mp.assign(n + 1, vector<int>(n + 1, 0));
		slk.assign(n + 1, INF);
		lx.assign(n + 1, 0);
		ly.assign(n + 1, 0);
		vx.assign(n + 1, 0);
		vy.assign(n + 1, 0);
		mx.assign(n + 1, -1);
		my.assign(n + 1, -1);
	}
	bool dfs(int x, int yes) {
		if(vx[x] == ii) return 0;
		vx[x] = ii;
		rep(i, 1, n) if(vy[i] != ii) {
			int val = lx[x] + ly[i] - mp[x][i];
			if(!val) {
				vy[i] = ii;
				if(my[i] == -1 || dfs(my[i], yes)) {
					if(yes) {
						mx[x] = i;
						my[i] = x;
					}
					return 1;
				}
			}
			else  slk[i] = min(slk[i], val);
		}
		return 0;
	}
	bool augment(int x) {
		rep(i, 1, n) if(slk[i] == 0 
			&& (my[i] == -1 || dfs(my[i], 0))) return 1;
		return 0;
	}
	void relabel() {
		int val = INF;
		rep(i, 1, n) if(vy[i] != ii) val = min(val, slk[i]);
		rep(i, 1, n) if(vx[i] == ii) lx[i] -= val;
		rep(i, 1, n) if(vy[i] == ii) ly[i] += val;
		rep(i, 1, n) if(vy[i] != ii) slk[i] -= val;
		return;
	}
	int solve() {
		rep(i, 1, n) rep(j, 1, n) 
			lx[i] = max(lx[i], mp[i][j]);
		rep(i, 1, n) {
			 ii++;
			 rep(j, 1, n) slk[j] = INF;
			 if(dfs(i, 1)) continue;
			 while(!augment(i)) relabel();
			 ii++, assert(dfs(i, 1));
		}
		int ans = 0;
		rep(i, 1, n) ans += mp[i][mx[i]];
		return ans;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; 
	while(cin >> n && n) {
		KM km; km.init_(n);
		rep(i, 1, n) rep(j, 1, n) {
			cin >> km.mp[i][j];
			km.mp[i][j] = max(0ll, km.mp[i][j]);
		}
		cout << km.solve() << "\n";
	}
	return 0;
}


