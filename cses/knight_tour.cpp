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
#define x first
#define y second
namespace solver {
	int x, y, yes, tot = 0;
	const int P = 8;
	int vis[P + 1][P + 1], cnt[P + 1][P + 1];
	int dirx[] = {2, -2, 1, -1, 2, -2, 1, -1};
	int diry[] = {1, 1, 2, 2, -1, -1, -2, -2};
	void init_(int _x, int _y) {
		x = _x, y = _y, yes = 0;
	}
	int deg(int x, int y) {
		int cnt = 0;
		rep(i, 0, 7) {
			int nx = x + dirx[i];
			int ny = y + diry[i];
			if(nx < 1 || nx > P || ny < 1 || ny > P) continue;
			if(vis[nx][ny]) continue;
			cnt ++;
		}
		return cnt;
	}
	void dfs(int x, int y, int mv) {
		if(yes) return;
		vis[x][y] = mv;
		tot ++;
		if(tot % 10000000 == 0) print(tot);
		if(mv == 64) {
			yes = 1;
			return;
		}
		vector<pair<int, pii>> pos;
		rep(i, 0, 7) {
			int nx = x + dirx[i];
			int ny = y + diry[i];
			if(nx < 1 || nx > P || ny < 1 || ny > P) continue;
			if(vis[nx][ny]) continue;
			pos.push_back({deg(nx, ny), {nx, ny}});
		}
		sort(all(pos));
		for(auto i : pos) {
			int nx = i.y.x, ny = i.y.y;
			dfs(nx, ny, mv + 1);
			if(yes) return;
		}
		vis[x][y] = 0;
	}
	void solve() {
		dfs(y, x, 1);
		assert(yes);
		rep(i ,1, P) rep(j, 1, P) cout << vis[i][j] << " \n"[j == P];

	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int x, y;
	cin >> x >> y;
	init_(x, y);
	solve();
	return 0;
}


