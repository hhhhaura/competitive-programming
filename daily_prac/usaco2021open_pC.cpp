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
#define x first
#define y second
namespace solver {
	int n;
	vector<pii> a;
	vector<vector<vector<int>>> cur, nxt, cnt;
	pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	int sign(int a) { return a == 0 ? 0 : (a > 0 ? 1 : -1); }
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
		cur.assign(n, vector<vector<int>>(n, vector<int>(n, 0)));
		nxt.assign(n, vector<vector<int>>(n, vector<int>(n, 0)));
		cnt.assign(n, vector<vector<int>>(n, vector<int>(n, 0)));
	}
	bool onseg(pii a, pii b, pii o) {
		return sign(cross(a - o, b - o)) == 0 
			&& sign(dot(a - o, b - o)) <= 0;
	}
	int ori(pii a, pii b, pii o) {
		return sign(cross(a - o, b - o));
	}
	bool banana(pii a, pii b, pii c, pii d) {
		if(onseg(a, b, c) || onseg(a, b, d) ||
			onseg(c, d, a) || onseg(c, d, b)) return 1;
		if(ori(a, b, c) * ori(a, b, d) == -1 &&
			ori(c, d, a) * ori(c, d, b) == -1) return 1;
		return 0;
	}
	bool in_tri(vector<pii> a, pii o) {
		pii vec = {1, 1e9};
		int cnt = 0;
		cnt += banana(a[0], a[1], o, o + vec);
		cnt += banana(a[1], a[2], o, o + vec);
		cnt += banana(a[2], a[0], o, o + vec);
		return cnt & 1;
	}
	void solve() {
		rep(x, 0, n - 1) rep(y, 0, n - 1) rep(z, 0, n - 1) {
			if(x == y || x == z || y == z) continue;
			cnt[x][y][z] = 3;
			rep(o, 0, n - 1) if(x != o && y != o && z != o)
				cnt[x][y][z] += in_tri({a[x], a[y], a[z]}, a[o]);
		}
		rep(x, 0, n - 1) rep(y, 0, n - 1) rep(z, 0, n - 1) 
			cur[x][y][z] = 1;
		rep(i, 4, n) {
			rep(x, 0, n - 1) rep(y, 0, n - 1)
				rep(z, 0, n - 1) nxt[x][y][z] = 0;
			rep(x, 0, n - 1) rep(y, 0, n - 1) 
				rep(z, 0, n - 1) if(cnt[x][y][z] >= i){
				int tot = 0;
				tot += cur[x][y][z] * (cnt[x][y][z] - i + 1);
				vector<pii> v = {a[x], a[y], a[z]};
				rep(to, 0, n - 1) if(in_tri(v, a[to])){
					if(to == x || to == y || to == z) continue;
					tot += cur[x][y][to];
					tot += cur[x][to][z];
					tot += cur[to][y][z];
				}
				tot %= MOD;
				nxt[x][y][z] = tot;
			}
			cur.swap(nxt);
		}
		int ans = 0;
		rep(x, 0, n - 1) rep(y, 0, n - 1)
			rep(z, 0, n - 1) ans += cur[x][y][z];;
		ans %= MOD;
		cout << ans << "\n";
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) cin >> a[i].x >> a[i].y;
	solve();
	return 0;
}

