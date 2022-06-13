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
	string s;
	const int P = 7;
	int ans, cnt[4], tot = 0;
	int path[P * P];
	int dirx[] = {-1, 1, 0, 0};
	int diry[] = {0, 0, -1, 1};
	bool v[P + 2][P + 2];
	void dfs(int st, int x, int y) {
		tot ++;
		if(x == P && y == 1) ans += (st == 48);
		else if(v[x-1][y]&&v[x+1][y]&&!v[x][y-1]&&!v[x][y+1])return;
		else if(!v[x-1][y]&&!v[x+1][y]&&v[x][y-1]&&v[x][y+1])return;
		else rep(i, 0, 3) if(path[st] == -1 || path[st] == i){
			int nx = dirx[i] + x;
			int ny = diry[i] + y;
			if(v[nx][ny]) continue;
			v[nx][ny] = 1;
			dfs(st + 1, nx, ny);
			v[nx][ny] = 0;
		}
	}
	void solve() {
		ans = 0;
		rep(i, 0, 47) {
			if(s[i] == '?') path[i] = -1;
			else if(s[i] == 'U') path[i] = 0;
			else if(s[i] == 'D') path[i] = 1;
			else if(s[i] == 'L') path[i] = 2;
			else path[i] = 3;
		}
		rep(i, 0, P + 1) v[0][i] = 1;
		rep(i, 0, P + 1) v[i][0] = 1;
		rep(i, 0, P + 1) v[P + 1][i] = 1;
		rep(i, 0, P + 1) v[i][P + 1] = 1;
//		rep(i, 6, 18) {
//			cnt[2] = cnt[3] = i;
//			cnt[0] = 21 - i;
//			cnt[1] = cnt[0] + 6;
//			v[1][1] = 1;
//			dfs(0, 1, 1);
//		}
		v[1][1] = 1;
		dfs(0, 1, 1);
		print(tot);
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> s;
	solve();
	return 0;
}


