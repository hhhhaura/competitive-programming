#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define ll long long int
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
	const int P = 10000000;
	struct node {
		int l, r; ll val;
	};
	int n, ii = 1;
	const int mn = 1, mx = 2000000;
	vector<node> v(P, {0, 0, 0});
	vector<int> cnt, root;
	int copy(int nd) {
		v[++ii] = v[nd];
		return ii;
	}
	void build(int nd, int L, int R) {
		int mid = (L + R) / 2;
		if(L == R) v[nd] = {cnt[L], cnt[L],  (ll) L * cnt[L] * cnt[L]};
		else {
			v[nd].l = ++ii;
			v[nd].r = ++ii;
			build(v[nd].l, L, mid);
			build(v[nd].r, mid + 1, R);
			v[nd].val = v[v[nd].l].val + v[v[nd].r].val;
		}
	}
	void init_(int _n) {
		n = _n;
		cnt.assign(mx + 1, 0);
		root.assign(n + 1, 0);
		root[0] = 1;
	}
	void modify(int pre, int cur, int L, int R, int id, int x) {
		if(L == R) {
			int cnt = x + v[cur].l;
			v[cur] = {cnt, cnt, (ll) cnt * cnt * L};
		}
		else {
			int mid = (L + R) / 2;
			if(id <= mid) {
				if(!v[pre].l) v[cur].l = ++ii;
				else v[cur].l = copy(v[pre].l);
				modify(v[pre].l, v[cur].l, L, mid, id, x);
			}
			else {
				if(!v[pre].r) v[cur].r = ++ii;
				else v[cur].r = copy(v[pre].r);
				modify(v[pre].r, v[cur].r, mid + 1, R, id, x);
			}
			v[cur].val = v[v[cur].l].val + v[v[cur].r].val;
		}
	}
	void solve() {
		build(1, mn, mx);
		ll ans = v[1].val;
		rep(i, 1, n) {
			int s, x;
			cin >> s >> x;
			root[i] = copy(root[s]);
			modify(root[s], root[i], mn, mx, abs(x), (x < 0 ? -1 : 1));
			ans ^= v[root[i]].val;
		}
		cout << ans << "\n";
	}
	
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_(k);
	rep(i, 1, n) {
		int x; cin >> x;
		cnt[x] ++;
	}
	solve();
	return 0;
}


