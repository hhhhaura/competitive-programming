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
#define x first
#define y second
namespace solver {
	int n;
	pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
	pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	int sign(int x) { return (x == 0 ? 0 : (x < 0 ? 1 : -1)); }
	lld len(pii a) { return sqrt(a.x * a.x + a.y * a.y); }
	lld dis(pii a, pii b, pii o) { return abs(cross(a - b, o - b) / len(b - a)); }
	vector<pii> p;
	vector<pair<pii, int>> v;
	vector<int> pos, a;
	void init_(int _n) {
		n = _n;
		p.assign(n, {0, 0});
		pos.assign(n, 0);
		a.assign(n, 0);
		iota(all(a), 0);
	}
	void solve() {
		rep(i, 0, n - 1) rep(j, 0, n - 1) if(i != j) {
			v.push_back({{i, j}, 0});
			v.push_back({{i, j}, 1});
		}
		auto cmp = [&](pii a, pii b) {
			bool foo1 = (a.y > 0 || (a.y == 0 && a.x > 0));
			bool foo2 = (b.y > 0 || (b.y == 0 && b.x > 0));
			if(foo1 != foo2) return foo1 > foo2;
			else return cross(a, b) > 0;
		};
		sort(all(v), [&](pair<pii, int> a, pair<pii, int> b){
			pii L = p[a.first.y] - p[a.first.x];
			pii R = p[b.first.y] - p[b.first.x];
			if(a.second) L = {L.y, -L.x};
			if(b.second) R = {R.y, -R.x};
			return cmp(L, R);
		});
		sort(all(a), [&](int x, int y) {
			if(p[x].y != p[y].y) return p[x].y < p[y].y;
			else return p[x].x < p[y].x;
		});
		rep(i, 0, n - 1) pos[a[i]] = i;
		lld ans = 0;
		for(auto i : v) {
			int tp = i.second;
			pii cur = i.first;
			if(tp == 0) {
				int L = pos[cur.x] - 1, R = pos[cur.y] + 1;
				if(L >= 0) ans = max(ans, dis(p[cur.x], p[cur.y], p[a[L]]));
				if(R < n) ans = max(ans, dis(p[cur.x], p[cur.y], p[a[R]]));
				swap(pos[cur.x], pos[cur.y]);
				a[pos[cur.x]] = cur.x;
				a[pos[cur.y]] = cur.y;
			}
			else {
				int a = pos[cur.first], b = pos[cur.second];
				if(b - a == 1) ans = max(ans, len(p[cur.first] - p[cur.second]));
			}
		}
		cout << fixed << setprecision(12);
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) cin >> p[i].x >> p[i].y;
	solve();
	return 0;
}

