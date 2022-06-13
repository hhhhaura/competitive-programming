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
#define LL long long int
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
	int n, k, ii;
	const int P = 4500000;
	int mn = 0, mx = 0;
	struct node {
		int l, r, cnt;
		LL val;
	};
	vector<node> v(P, {0, 0, 0, 0});
	vector<int> a, t;
	vector<LL> dp, pre;
	void init_(int _n, int _k) {
		n = _n, k = _k, ii = 1;
		a.assign(n + 1, 0);
		t.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		pre.assign(n + 1, 0);
	}
	int copy(int x) {
		v[++ii] = v[x];
		return ii;
	}
	node pull(int l, int r) {
		return {l, r, v[l].cnt + v[r].cnt, v[l].val + v[r].val};
	}
	void modify(int a, int b, int L, int R, int id, int val) {
		if(L == R) {
			v[b].val += id * val;
			v[b].cnt += val;
		}
		else {
			int mid = -(abs(L + R) / 2);
			if(id <= mid - 1) {
				if(!v[a].l) v[a].l = ++ii;
				v[b].l = copy(v[a].l);
				modify(v[a].l, v[b].l, L, mid - 1, id, val);
			}
			else {
				if(!v[a].r) v[a].r = ++ii;
				v[b].r = copy(v[a].r);
				modify(v[a].r, v[b].r, mid, R, id, val);
			}
			v[b] = pull(v[b].l, v[b].r);
			
		}
	}
	LL query(int l, int r, int L, int R, int cnt) {
		if(L == R) {
			return (LL) min(cnt, v[r].cnt - v[l].cnt) * L;
		}
		else {	
			int ll = v[l].l, rl = v[r].l;
			int lr = v[l].r, rr = v[r].r;
			int val = v[rl].cnt - v[ll].cnt;
			int mid = -(abs(L + R) / 2);
			if(val >= cnt) return query(ll, rl, L, mid - 1, cnt);
			else return (v[rl].val - v[ll].val) + 
				query(lr, rr, mid, R, cnt - val);
		}
	} 
	void CDQ(int L, int R, int l, int r) {
		int mid = (L + R) / 2, id = l;
		LL best = 0;
		rep(i, l, min(r, mid)) {
			LL val = query(t[i - 1], t[mid], mn, mx, k);
			LL ans = pre[mid] - pre[i - 1] - val;
			if(ans > best) best = ans, id = i;
		}
		dp[mid] = best;
		if(L != R) {
			CDQ(L, mid, l, id);
			CDQ(mid + 1, R, id, r);
		}
	}
	void solve() {
		t[0] = 1;
		rep(i, 1, n) mn = min(a[i], mn);
		rep(i, 1, n) {
			pre[i] = pre[i - 1] + a[i];
			t[i] = copy(t[i - 1]);
			if(a[i] < 0) modify(t[i - 1], t[i], mn, mx, a[i], 1);
		}
		CDQ(1, n, 1, n);
		LL ans = 0;
		rep(i, 1, n) ans = max(ans, dp[i]);
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; 
	cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) cin >> a[i];
	solve();
	return 0;
}

