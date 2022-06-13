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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<int> a(n + 2, 0);
	vector<int> L(n + 1, 0), R(n + 1, n + 1);
	rep(i, 1, n) cin >> a[i];
	vector<int> st(1, 0);
	rep(i, 1, n) {
		while(a[st.back()] >= a[i]) st.pop_back();
		L[i] = st.back();
		st.push_back(i);
	}
	st = {n + 1};
	rrep(i, 1, n) {
		while(a[st.back()] >= a[i]) st.pop_back();
		R[i] = st.back();
		st.push_back(i);
	}
	int ans = 0;
	rep(i, 1, n) ans = max(ans, (R[i] - L[i] - 1) * a[i]);
	cout << ans << "\n";
	return 0;
}


