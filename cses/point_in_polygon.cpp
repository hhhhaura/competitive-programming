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

#define INF 2000000001
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
#define x first
#define y second
namespace solver {
	pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	vector<pii> v;
	int n;
	void init_(int _n) {
		n = _n;
		v.assign(n, {0, 0});
	}
	int sign(int a) {
		if(a == 0) return 0;
		else return (a > 0 ? 1 : -1);
	}
	int ori(pii a, pii b, pii c) {
		return sign(cross(a - c, b - c));
	}
	bool onseg(pii a, pii b, pii c) {
		return sign(dot(a - c, b - c)) <= 0 &&
			sign(cross(a - c, b - c)) == 0;
	}
	bool banana(pii a, pii b, pii c, pii d) {
		if(onseg(a, b, c) || onseg(a, b, d) ||
			onseg(c, d, a) || onseg(c, d, b)) return 1;
		if(ori(a, b, c) * ori(a, b, d) == -1 &&
			ori(c, d, a) * ori(c, d, b) == -1) return 1;
		return 0;
	}
	int query(int x, int y) {
		int cnt = 0;
		pii vec = {1, INF}, cur = {x, y};
		rep(i, 0, n - 1) {
			int l = i, r = (i + 1 == n ? 0 : i + 1);
			if(onseg(v[l], v[r], cur)) return 0;
			cnt += banana(v[l], v[r], cur, cur + vec);
		}
		if(cnt & 1) return 1;
		else return 2;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; 
	cin >> n >> m;
	init_(n);
	rep(i, 0, n - 1) cin >> v[i].x >> v[i].y;
	rep(i, 1, m) {
		int x, y;
		cin >> x >> y;
		int ans = query(x, y);
		if(ans == 0) cout << "BOUNDARY\n";
		else if(ans == 1) cout << "INSIDE\n";
		else cout << "OUTSIDE\n";
	}
	
	return 0;
}



