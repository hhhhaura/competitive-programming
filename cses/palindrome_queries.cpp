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
	int n; string s;
	const int w = 37;
	vector<int> pre;
	struct node {
		int len, val, rev, yes;
	};
	vector<node> v;
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	node pull(node l, node r) {
		if(!l.yes) return r;
		if(!r.yes) return l;
		return {
			l.len + r.len, 
			(l.val + r.val * pre[l.len] % MOD) % MOD,
			(r.rev + l.rev * pre[r.len] % MOD) % MOD,
			1
		};
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int val = s[L - 1] - 'a' + 1;
		if(L == R) v[nd] = {1, val, val, 1};
		else {
			build(L, mid), build(mid + 1, R);
			v[nd] = pull(v[get(L, mid)], v[get(mid + 1, R)]);
		}
	}
	void init_(int _n, string _s) {
		n = _n, s = _s;
		pre.assign(n + 1, 1);
		v.assign(2 * n + 1, {0, 0, 0, 0});
		rep(i, 1, n) pre[i] = pre[i - 1] * w % MOD; 
		build(1, n);
	}
	void modify(int L, int R, int id, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) v[nd] = {1, val, val, 1};
		else {
			if(id <= mid) modify(L, mid, id, val);
			else modify(mid + 1, R, id, val);
			v[nd] = pull(v[get(L, mid)], v[get(mid + 1, R)]);
		}
	}
	node query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		node ans;
		if(l > R || r < L) return {0, 0, 0, 0};
		else if(l <= L && r >= R) ans = v[nd];
		else ans = pull(query(L, mid, l, r), query(mid + 1, R, l, r));
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	string s; cin >> s;
	init_(n, s);
	print("haha");
	rep(i, 1, m) {
		int tp; cin >> tp;
		if(tp == 1) {
			int a; cin >> a;
			char b; cin >> b;
			modify(1, n, a, b - 'a' + 1);
		}
		else {
			int a, b; cin >> a >> b;
			node ans = query(1, n, a, b);
			cout << (ans.val == ans.rev ? "YES\n" : "NO\n");
		}
	}
	return 0;
}


