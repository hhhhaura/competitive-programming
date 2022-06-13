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
struct BIT {
	int n, cnt;
	vector<int> v;
	vector<pii> ops;
	void init_(int _n) {
		n = _n, cnt = 0;
		ops.clear();
		v.assign(n + 1, 0);
	}
	int lowbit(int x) {
		return x & (-x);
	}
	void modify(int x, int val, int yes) {
		if(yes) ops.push_back({x, val}), cnt ++;
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
	void undo() {
		pii p = ops.back(); 
		ops.pop_back();
		modify(p.first, -p.second, 0);
		cnt--;
	}
};
namespace solver {
	int n, ops;
	const int P = 1000000;
	vector<int> a, yes, s, v;
	vector<pii> op;
	BIT bit; 
	void init_(int _n) {
		n = _n, ops = 0;
		a.assign(n + 1, 0);
		yes.assign(n + 1, 0);
		v.clear();
		s.clear();
		op.clear();
		while(bit.cnt) bit.undo();
	}
	void undo() {
		pii p = op.back(); op.pop_back();
		ops--;
		if(p.first) s.pop_back();
		else s.push_back(p.second);
	}
	void solve() {
		auto insert = [&](int x) {
			while(s.size() && a[s.back()] <= a[x]) {
				int cur = s.back(); s.pop_back();
				ops ++, op.push_back({0, cur});
				bit.modify(a[cur], -1, 1);
			}
			s.push_back(x);
			ops ++, op.push_back({1, x});
			bit.modify(a[x], 1, 1);	
		};
		int cur = 0, best = 0;
		rep(i, 1, n) {
			if(a[i] > best) {
				best = a[i];
				yes[i] = ++cur;
				v.push_back(i);
			}
		}
		int ans = cur;
		rrep(i, v[cur - 1] + 1, n) insert(i);
		rrep(i, 1, n) if(yes[i] > 1) {
			int pre = v[yes[i] - 2];
			int cnt1 = bit.cnt, cnt2 = ops;
			rrep(j, pre + 1, i - 1) insert(j);
			int val = bit.query(P) - bit.query(a[pre]);
			ans = max(ans, yes[i] - 1 + val);
			while(ops != cnt2) undo();
			while(bit.cnt != cnt1) bit.undo();
			rrep(j, pre + 1, i) insert(j);
		}
		cout << ans << "\n";
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	bit.init_(1000000);
	int t; cin >> t;
	while(t--) {
		int n;
		cin >> n; init_(n);
		rep(i, 1, n) cin >> a[i];
		solve();
	}
	return 0;
}


