#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define ramdon mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<__LINE__<<": ",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " ", ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ...e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m, A, B;
	vector<int> a, b, v, piv, val;
	vector<vector<pii>> q;
	vector<vector<int>> mp;
	void init_(int _n, int _A, int _B) {
		n = _n, A = _A, B = _B;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		piv.assign(n + 1, 0);
		q.assign(n + 1, vector<pii>());
	}
	void init2_(int _m) {
		m = _m;
	}
	int lowbit(int x) {
		return x & (-x);
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
	vector<int> cal(int x) {
		v.assign(n + 1, 0);
		piv.assign(n + 1, 0);
		vector<int> ans(m + 1, 0);
		rep(i, 1, n) {
			int num = b[i];
			if(piv[num] + 1 >= x) {
				int cur = piv[num];
				if(cur >= x) modify(mp[num][cur - x], -val[num]);
				modify(mp[num][cur - x + 1], val[num]);
			}
			for(auto j : q[i]) {
				int L = j.first, id = j.second;
				ans[id] = query(i) - query(L - 1);
			}
			piv[num] ++;
		}
		return ans;
	}
	void solve() {
		sort(all(val));
		val.resize(unique(all(val)) - val.begin());
		mp.assign(val.size(), vector<int>());
		rep(i, 1, n) {
			int id = lower_bound(all(val), a[i]) - val.begin();
			mp[id].push_back(i);
			b[i] = id;
		}
		print("gere");
		vector<int> x = cal(A);
		vector<int> y = cal(B + 1);
		rep(i, 1, m) cout << x[i] - y[i] << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, A, B;
	cin >> n >> A >> B;
	init_(n, A, B);
	rep(i, 1, n) {
		cin >> a[i];
		val.push_back(a[i]);
	}
	int m; cin >> m;
	init2_(m);
	rep(i, 1, m) {
		int L, R;
		cin >> L >> R;
		q[R].push_back({L, i});
	}
	solve();
	return 0;
}


