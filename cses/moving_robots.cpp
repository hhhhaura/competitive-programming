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
	lld dp[101][8][8], ans[64][8][8];
	vector<int> dirx = {0, 0, 1, -1};
	vector<int> diry = {1, -1, 0, 0};
	void solve(int K) {
		rep(x, 0, 7) rep(y, 0, 7) {
			rep(len, 0, K) rep(i, 0, 7) rep(j, 0, 7)
				dp[len][i][j] = 0;
			dp[0][x][y] = 1;
			rep(len, 0, K - 1) rep(i, 0, 7) rep(j, 0, 7) {
				int cnt = 0;
				rep(k, 0, 3) {
					int nx = i + dirx[k];
					int ny = j + diry[k];
					if(nx < 0 || ny < 0) continue;
					if(nx >= 8 || ny >= 8) continue;
					cnt ++;
				}
				rep(k, 0, 3) {
					int nx = i + dirx[k];
					int ny = j + diry[k];
					if(nx < 0 || ny < 0) continue;
					if(nx >= 8 || ny >= 8) continue;
					dp[len + 1][nx][ny] += dp[len][i][j] * (1.0 / cnt);
				}
			}
			rep(i, 0, 7) rep(j, 0, 7)
			 	ans[x * 8 + y][i][j] = dp[K][i][j];
		}
		lld sum = 0;
		rep(i, 0, 7) rep(j, 0, 7) {
			lld cur = 1;
			rep(k, 0, 63) cur *= (1 - ans[k][i][j]);
			sum += cur;
		}
		cout << fixed << setprecision(6);
		cout << sum << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int k; cin >> k;
	solve(k);
	return 0;
}


