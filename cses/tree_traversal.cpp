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
namespace solver {
	int n;
	vector<int> L, R, a, b, id, ans;
	void init_(int _n) {
		n = _n;
		L.assign(n + 1, 0);
		R.assign(n + 1, 0);
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		id.assign(n + 1, 0);
	}
	void solve(int l, int r, int st) {
		int piv = a[st], mid = id[piv];
		if(l >= r) return;
		int len = mid - l;
		if(len) {
			L[piv] = a[st + 1];
			solve(l, mid - 1, st + 1);
		}
		if(r - l - len) {
			R[piv] = a[st + len + 1];
			solve(mid + 1, r, st + 1 + len);
		}
	}
	void traverse(int cur) {
		if(L[cur]) traverse(L[cur]);
		if(R[cur]) traverse(R[cur]);
		ans.push_back(cur);
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	rep(i, 1, n) id[b[i]] = i;
	solve(1, n, 1);
	traverse(a[1]);
	rep(i, 0, n - 1) cout << ans[i] << " \n"[i + 1 == n];
	return 0;
}


