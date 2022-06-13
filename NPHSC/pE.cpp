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
	int n;
	vector<int> v;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, 0);
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
};
namespace solver {
	BIT bit;
	int n, q;
	vector<pii> qs;
	vector<int> v, a, pre;
	void init_(int _n, int _q) {
		n = _n, q = _q;
		qs.clear();
		v.clear();
		a.assign(n + 1, 0);
		pre.assign(n + 1, 0);
	}
	void solve() {
		int cur = 0;
		for(auto &i : qs) {
			if(i.first == 1) continue;
			int sum = 0;
			rep(j, 1, i.second) sum += a[++cur];
			i.second = sum;
			v.push_back(sum);
		}
		rep(i, 1, n) pre[i] = a[i] + pre[i - 1];
		sort(all(v)), v.resize(unique(all(v)) - v.begin());
		bit.init_(v.size() + 1);
		int tot = 0;
		rep(i, 0, q - 1) {
			int tp = qs[i].first;
			int val = qs[i].second;
			if(tp == 1) {
				int cur = lower_bound(all(pre), tot + val) - pre.begin();
				int id = lower_bound(all(v), a[cur]) - v.begin();
				int sum = bit.query(id);
				int x = (tot + val - pre[cur - 1] - 1 - sum) % a[cur];
				x = (x + a[cur]) % a[cur];
				cout << pre[cur - 1] + x + 1 << "\n";
			}
			else {
				int id = lower_bound(all(v), val) - v.begin() + 1;
				bit.modify(id, val);
				tot += val;
			}
		}
		return;
	}


	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	init_(n, q);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, q) {
		int tp, val;
		cin >> tp >> val;
		qs.push_back({tp, val});
	}
	solve();
	return 0;
}

