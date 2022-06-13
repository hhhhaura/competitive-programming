#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n;
	vector<int> a, b, tot, id, c, to;
	vector<int> dp, pre;
	vector<pii> v;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		id.assign(n + 1, 0);
		c.assign(n + 1, 0);
		to.assign(n + 1, 0);
		pre.assign(n + 2, 0);
		dp.assign(n + 2, 0);
		v.assign(n + 1, {0, 0});
	}
	int lowbit(int x) {
		return x & -x;
	}
	bool comp(pii a, pii b) {
		if(a.x != b.x) return a.x > b.x;
		else return to[a.y] > to[b.y];
	}
	void modify(int x, pii p) {
		for(int i = x; i <= n; i += lowbit(i)) {
			if(comp(p, v[i])) v[i] = p;
		}
	}
	pii query(int x) {
		pii ans = {0, 0};
		for(int i = x; i > 0; i -= lowbit(i)) {
			if(comp(v[i], ans)) ans = v[i];
		}
		return ans;
	}
	void solve() {
		sort(all(tot)), tot.resize(unique(all(tot)) - tot.begin());
		rep(i, 1, n) {
			int id2 = lower_bound(all(tot), a[i]) - tot.begin() + 1;
			int id1 = lower_bound(all(tot), b[i]) - tot.begin() + 1;
			a[i] = id2, b[i] = id1;
			id[b[i]] = i;
		}
		rep(i, 1, n) {
			c[i] = id[a[i]];
			to[i] = tot[a[i] - 1];
		}
		rrep(i, 1, n) {
			pii cur = query(n - c[i]);
			dp[i] = cur.x + 1;
			pre[i] = cur.y;
			modify(n - c[i] + 1, {dp[i], i});
		}
		pii ans = query(n);
		int cur = ans.y;
		rep(i, 1, ans.x - 1) {
			cout << to[cur] << " ";
			cur = pre[cur];
		}
		cout << to[cur] << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i], tot.push_back(a[i]);
	rep(i, 1, n) cin >> b[i];
	solve();
	return 0;
}

