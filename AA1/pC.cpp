
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
namespace solver {
	int n;
	vector<int> v, h, pre, ans;
	vector<pii> a;
	set<int> s;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, 0);
		h.assign(n + 1, 0);
		pre.assign(n + 2, 0);
		ans.clear();
		a.clear();
		s.clear();
	}
	void solve() {
		sort(all(a));
		rep(i, 1, n) {
			int id = lower_bound(all(a), pii(v[i] + h[i], -INF)) - a.begin();
			pre[id + 1] ++;
		}
		int ii = 1;
		rep(i, 1, n) {
			while(pre[ii] += pre[ii - 1], ii <= n && !pre[ii]) {
				s.insert(a[ii - 1].second);
				ii++;
			}
			auto it = s.begin();
			ans.push_back(*it);
			int id = lower_bound(all(a), pii(v[*it] + h[*it], -INF)) - a.begin();
			pre[id + 1] --;
			s.erase(it);
		}
		rep(i, 0, n - 1) cout << ans[i] << " \n"[i + 1 == n];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) {
			cin >> h[i] >> v[i];
			a.push_back({h[i], i});
		}
		solve();
	}
	return 0;
}

