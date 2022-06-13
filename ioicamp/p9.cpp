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
	vector<int> up, down, pos, tot;
	vector<pair<int, pii>> v;
	struct seg {
		int l, r, id;
	};
	void init_() {
		tot.clear();
		v.clear();
	}
	int cal(int L, int R) {
		return max(0ll, (down[L] - up[R]) * (pos[R] - pos[L]));
	}
	int bs(int l, int r, int a, int b) {
		int L = l, R = r;
		while(R - L > 1) {
			int mid = (L + R) / 2;
			if(cal(a, mid) <= cal(b, mid)) R = mid;
			else L = mid;
		}
		return R;
	}
	void solve() {
		sort(all(tot));
		tot.resize(unique(all(tot)) - tot.begin());
		sort(all(v));
		n = tot.size();
		up.assign(n + 1, -1);
		down.assign(n + 1, -1);
		pos.assign(n + 1, 0);
		rep(i, 1, n) pos[i] = tot[i - 1];
		for(auto i : v) {
			int id = lower_bound(all(tot), i.first) - tot.begin() + 1;
			int tp = i.second.first, h = i.second.second;
			if(tp == 0) up[id] = h;
			if(tp == 1) down[id] = h;
			if(up[id] == -1) up[id] = up[id - 1];
			if(down[id] == -1) down[id] = down[id - 1];
		}
		
		vector<seg> q(n + 1, {0, 0, 0});
		int l = 0, r = 0, ans = 0;
		q[0] = {1, n, 1};
		rep(i, 2, n) {
			while(q[l].r < i) l++;
			int cur = cal(q[l].id, i);
			ans = max(ans, cur);
			while(l < r && cal(q[r].id, q[r].l) 
				<= cal(i, q[r].l)) r--;
			int to = bs(q[r].l, q[r].r, q[r].id, i);
			q[r].r = to - 1;
			q[++r] = {to, n, i};
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	int x = 0, y = 0;
	v.push_back({0, {0, 0}}), tot.push_back(0);
	for(int i = 1; i <= n; i += 2) {
		int r, d; cin >> r >> d;
		v.push_back({x + r, {0, y}});
		tot.push_back(x + r);
		y += d, x += r;
	}
	int m; cin >> m;
	x = 0, y = 0;
	for(int i = 1; i <= m; i += 2) {
		int d, r; cin >> d >> r;
		v.push_back({x, {1, y + d}});
		tot.push_back(x);
		x += r, y += d;
	}
	solve();
	return 0;
}



