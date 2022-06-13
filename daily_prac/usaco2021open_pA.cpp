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
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	BIT bit; bit.init_(n);
	vector<int> a(n + 1, 0), pre(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	int ans = 0;
	rep(i, 1, n) {
		int to = pre[a[i]];
		int val = bit.query(i) - bit.query(to);
		if(to) ans += val;
		else ans += val;
		if(to) bit.modify(to, -1);
		bit.modify(i, 1);
		pre[a[i]] = i;
	}
	cout << ans << "\n";
	return 0;
}

