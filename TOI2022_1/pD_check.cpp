#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
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
	vector<pii> a;
	vector<vector<int>> v, l, r, b;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
		l.assign(n, vector<int>(n, 0));
		r.assign(n, vector<int>(n, 0));
		b.assign(n, vector<int>());
		rep(i, 0, n - 1) {
			rep(j, 0, n - 1) if(i != j) 
				b[i].push_back(j);
		}
	}
	bool check(pii a, pii b, pii c) {
		return cross(b - a, c - a) >= 0;
	}
	vector<vector<int>> calculate() {
		vector<vector<int>> s(n, vector<int>(n, 0));
		rep(i, 0, n - 1) {
			v.assign(n, vector<int>(n, 0));
			rep(x, i + 1, n - 1) v[i][x] = 1;
			rep(x, i + 1, n - 1) {
				vector<int> L, R;
				for(auto y : b[x]) if(y > i) {
					if(y > x) R.push_back(y);
					else L.push_back(y);
				}
				int ii = 0, sum = 0;
				rep(y, 0, signed(R.size()) - 1) {
					while(ii < L.size() && 
						check(a[L[ii]], a[x], a[R[y]])) {
						sum = (sum + v[L[ii]][x]) % MOD;
						ii++;
					}
					v[x][R[y]] = (sum + v[x][R[y]]) % MOD;
				}
			}
			rep(j, i, n - 1) rep(k, j + 1, n - 1)
				s[i][k] = (s[i][k] + v[j][k]) % MOD;
		}
		return s;
	}
	void solve() {
		sort(all(a));
		rep(i, 0, n - 1) {
			sort(all(b[i]), [&](int x, int y) {
				pii pa = a[x] - a[i];
				pii pb = a[y] - a[i];
				int foo1 = (pa.x == 0 ? pa.y < 0 : pa.x > 0);
				int foo2 = (pb.x == 0 ? pb.y < 0 : pb.x > 0);
				if(foo1 != foo2) return foo1 > foo2;
				else return cross(pa, pb) > 0;
			});
		}
		vector<vector<int>> l = calculate();
		reverse(all(a));
		rep(i, 0, n - 1) {
			sort(all(b[i]), [&](int x, int y) {
				pii pa = a[x] - a[i];
				pii pb = a[y] - a[i];
				int foo1 = (pa.x == 0 ? pa.y > 0 : pa.x < 0);
				int foo2 = (pb.x == 0 ? pb.y > 0 : pb.x < 0);
				if(foo1 != foo2) return foo1 > foo2;
				else return cross(pa, pb) > 0;
			});
		}
		vector<vector<int>> r = calculate();
		int ans = 0;
		rep(i, 0, n - 1) rep(j, i + 1, n - 1) {
			int val = l[i][j] * r[n - j - 1][n - i - 1] % MOD;
			ans = (ans + val - 1) % MOD;
		}
		cout << (ans + MOD) % MOD << "\n";
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

