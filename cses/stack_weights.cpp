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
	int n;
	vector<int> L, R, tag, mn;
	vector<pii> op;
	void init_(int _n) {
		n = _n;
		L.assign(n, 0);
		R.assign(n, 0);
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int l = get(L, mid), r = get(mid + 1, R);
		if(tag[nd]) {
			int val = tag[nd];
			mn[l] += val;
			tag[l] += val;
			mn[r] += val;
			tag[r] += val;
			tag[nd] = 0;
		}
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		mn[nd] = min(mn[get(L, mid)], mn[get(mid + 1, R)]);
	}
	void modify(int L, int R, int l, int r, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		if(L != R) push(L, R);
		if(l <= L && r >= R) {
			tag[nd] += val;
			mn[nd] += val;
		}
		else {
			modify(L, mid, l, r, val);
			modify(mid + 1, R, l, r, val);
			pull(L, R);
		}
	}
	void operate(vector<int> &ans) {
		tag.assign(2 * n + 1, 0);
		mn.assign(2 * n + 1, 0);
		int cnt = 0;
		rep(i, 0, n - 1) {
			int tp = op[i].y, num = op[i].x;
			cnt += tp;
			modify(1, n, 1, num, tp);
			if(cnt >= 0 && mn[get(1, n)] >= 0) ans[i] = 1;
		}
		return;
	}
	void solve() {
		operate(L);
		rep(i, 0, n - 1) op[i].y *= -1;
		operate(R);
		rep(i, 0, n - 1) {
			if(L[i]) cout << ">\n";
			else if(R[i]) cout << "<\n";
			else cout << "?\n";
		}
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) {
		int num, tp;
		cin >> num >> tp;
		op.push_back({num, (tp == 1 ? 1 : -1)});
	}
	solve();
	return 0;
}


