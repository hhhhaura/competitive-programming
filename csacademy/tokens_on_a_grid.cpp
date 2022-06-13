#define wiwihorz
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
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
	int n, m;
	const int P = 26;
	vector<int> dp, gray, sz, dif;
	vector<vector<int>> cnt, cal, mp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		dp.assign(1 << n, 1);
		sz.assign(1 << n, 0);
		gray.assign(1 << n, 0);
		dif.assign(1 << n, 0);
		cnt.assign(m, vector<int>(P, 0));
		cal.assign(m, vector<int>(1 << n, 0));
		mp.assign(m, vector<int>(n, 0));
	}
	int get_gray(int x) {
		int cur = 0;
		rep(i, 0, n - 1) cur |= 
			(((x >> i) ^ (x >> (i + 1))) & 1) << i;
		return cur;
	}
	void solve() {
		rep(i, 0, m - 1) rep(j, 0, n - 1) {
			if(mp[i][j] != -1) cnt[i][mp[i][j]] ++;
		}
		rep(i, 0, (1 << n) - 1) gray[i] = get_gray(i);
		rep(i, 1, (1 << n) - 1) dif[i] 
			= 31 - __builtin_clz(gray[i - 1] ^  gray[i]);
		rep(k, 0, m - 1) {
			int cur = 0;
			rep(i, 0, P - 1) cur = (cur + (1 << cnt[k][i]) - 1) % MOD;
			cal[k][0] = cur + 1;
			rep(i, 1, (1 << n) - 1) {
				int val = mp[k][dif[i]];
				if(val != -1) {
					cur = (cur - (1 << cnt[k][val]) + 1);
					cnt[k][val] += (gray[i - 1] > gray[i] ? 1 : -1);
					cur = (cur + (1 << cnt[k][val]) - 1);
					if(cur < 0) cur += MOD;
					if(cur >= MOD) cur -= MOD;
				}
				cal[k][gray[i]] = cur + 1;
			}
		}
		rep(i, 0, (1 << n) - 1) sz[i] = __builtin_popcount(i);
		rep(j, 0, m - 1) rep(i, 0, (1 << n) - 1)
			dp[i] = (dp[i] * cal[j][i]) % MOD;
		vector<int> tot(n + 1, 0);
		int mask = (1 << n) - 1;
		rep(i, 0, (1 << n) - 1) {
			int cur = mask ^ i, ans = 0;
			for(int j = cur; j > 0; j = (j - 1) & cur) {
				int id = (sz[i] - sz[mask ^ j]) & 1;
				ans = (ans + dp[mask ^ j] * (id ? -1 : 1));
				if(ans < 0) ans += MOD;
				if(ans >= MOD) ans -= MOD;
			}
			int id = (sz[mask] - sz[i]) & 1;
			ans = (ans + (id ? -1 : 1)) % MOD;
			tot[sz[i]] = (tot[sz[i]] + ans) % MOD;
		}
		rep(i, 0, n) cout << (tot[i] + MOD) % MOD << " \n"[i == n];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 0, n - 1) rep(j, 0, m - 1) {
		char c; cin >> c;
		mp[j][i] = (c == '.' ? -1 : c - 'a');
	}
	solve();
	return 0;
}


