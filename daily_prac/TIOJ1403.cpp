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

#define INF 1000000
#define MOD 1000000007
#define eps (1e-9)
#define int long long int
#define lld float
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
	vector<int> x, s, v;
	void init_(int _n) {
		n = _n;
		x.assign(n + 1, 0);
		s.assign(n + 1, 0);
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & -x;
	}
	void modify(int x, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			v[i] += val;
		}
	}
	int query(int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += v[i];
		}
		return ans;
	}
	int calculate(lld t) {
		vector<pair<lld, int>> tp;
		rep(i, 1, n) {
			lld to = x[i] + t * s[i];
			tp.push_back({to, i});
		}
		sort(all(tp));
		rep(i, 1, n) v[i] = 0;
		int ans = 0;
		rep(i, 0, n - 1) {	
			int id = tp[i].y;
			ans += query(n - id + 1);
			modify(n - id + 1, 1);
		}
		return ans;
	}
	void solve() {
		int ans = calculate(INF);
		lld L = 0, R = INF;
		rep(i, 1, 25) {
			lld mid = (L + R) / 2;
			if(calculate(mid) >= 10000) R = mid;
			else L = mid;
		}
		cout << ans % INF << "\n";
		set<int> ss;
		vector<pair<lld, int>> tp;
		rep(i, 1, n) {
			lld to = x[i] + R * s[i];
			tp.push_back({to, i});
		}
		sort(all(tp));
		vector<pair<pair<lld, lld>, pii>> tot;
		rep(i, 0, n - 1) {
			int id = tp[i].y;
			auto it = ss.lower_bound(id);
			// when the same ? 
			while(it != ss.end()) {
				lld t = (lld) (x[*it] - x[id]) / (s[id] - s[*it]);
				tot.push_back({
					{t, x[id] + s[id] * t},
					{id, *it}
				});
				it = next(it);
			}
			ss.insert(id);
		}
		sort(all(tot));
		int mn = min(10000ll, (int)(tot.size()));
		rep(i, 0, mn - 1) cout << tot[i].y.x << " " << tot[i].y.y << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> x[i] >> s[i];
	solve();
	return 0;
}


