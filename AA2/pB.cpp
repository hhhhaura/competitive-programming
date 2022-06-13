#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__, kout("["+string(#a)+"] = ", a)
void kout() { cerr << endl; }
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
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
	int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
	int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
	int sign(int x) { return (x == 0 ? 0 : (x < 0 ? -1 : 1)); }
	vector<pii> a;
	vector<int> v, b;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
		b.assign(n, 0);
		rep(i, 0, n - 1) b[i] = i;
		v.clear();
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
	bool check() {
		rep(i, 0, n - 1) {
			int L = (i - 1 < 0 ? i - 1 + n : i - 1);
			int R = (i + 1 >= n ? i + 1 - n : i + 1);
			rep(j, 0, n - 1) {
				if(j == L || j == R || j == i) continue;
				int nxt = (j + 1 >= n ? j + 1 - n : j + 1);
				if(banana(a[i], a[R], a[j], a[nxt])) return 0;
			}
		}
		return 1;
	}
	int cal_area() {
		int ans = 0;
		rep(i, 0, n - 1) {
			int nxt = (i + 1 >= n ? i + 1 - n : i + 1);
			ans += cross(a[i] - a[0], a[nxt] - a[0]);
		}
		return ans;
	}
	void solve(int k) {
		sort(all(a));
		do {
			if(!check()) continue;
			int cur = cal_area();
			if(cur > 0) {
				v.push_back(cur);
			}
		} while(next_permutation(all(a)) && next_permutation(all(b)));
		sort(all(v));
		print(v.size());
		int ans = v[n * k - 1];
		cout << (ans / 2) << "." << ((ans & 1) ? 5 : 0) << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) cin >> a[i].x >> a[i].y;
	int k; cin >> k;
	solve(k);
	return 0;
}


