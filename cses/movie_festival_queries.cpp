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
	int n, m, lg;
	const int P = 1000000;
	vector<vector<pair<pii, int>>> op;
	vector<pii> a;
	vector<int> ans, st;
	vector<vector<int>> to;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		lg = 31 - __builtin_clz(n);
		op.assign(P + 1, vector<pair<pii, int>>());
		a.assign(n + 2, {0, 0});
		ans.assign(m + 1, 0);
		to.assign(lg + 1, vector<int>(n + 2, 0));
	}
	void solve() {
		a[n + 1] = {INF, INF};
		 sort(all(a), [](pii a, pii b) {
		 	if(a.y == b.y) return a.x < b.x;
			else return a.y < b.y;
		 });
		 st.push_back(n + 1);
		 to[0][n + 1] = n + 1;
		 rep(i, 1, n) op[a[i].x].push_back({{i, a[i].y}, -1});
		 rrep(i, 1, n) {
		 	int L = 0, R = st.size();
			while(R - L > 1) {
				int mid = (L + R) / 2;
				if(a[st[mid]].x >= a[i].y) L = mid;
				else R = mid;
			}
			to[0][i] = st[L];
			while(st.size() && a[st.back()].x <= a[i].x) st.pop_back();
			st.push_back(i);
		 }
		 rep(i, 1, lg) rep(j, 1, n + 1) {
		 	to[i][j] = to[i - 1][to[i - 1][j]];
		 }
		 int cur = n + 1;
		 auto gogo = [&](int x, int R) {
		 	if(a[x].y > R) return 0ll;
			int ans = 1;
			rrep(i, 0, lg) {
				int val = to[i][x];
				if(a[val].y <= R) {
					ans += (1 << i);
					x = val;
				}
			}
			return ans;
		 };
		 rrep(i, 1, P) {
		 	for(auto j : op[i]) if(j.y == -1) {
				int pos = j.x.x, R = j.x.y;
				if(a[cur].y > R) cur = pos;
			}
			for(auto j : op[i]) if(j.y != -1) {
				int L = j.x.x, R = j.x.y, id = j.y;
				ans[id] = gogo(cur, R);
			}
		 }
		 rep(i, 1, m) cout << ans[i] << "\n";
		 
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n, m);
	rep(i, 1, n) cin >> a[i].x >> a[i].y;
	rep(i, 1, m) {
		int L, R;
		cin >> L >> R;
		op[L].push_back({{L, R}, i});
	}
	solve();
	return 0;
}


