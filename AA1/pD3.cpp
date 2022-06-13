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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		vector<int> a(n + 1, 0), v;
		rep(i, 1, n) cin >> a[i];
		int best = 0, ans = 0, sz = 0;
		rep(i, 1, n) {
			if(best < a[i]) v.push_back(i);
			best = max(best, a[i]);
		}
		sz = v.size();
		v.push_back(n + 1);
		rep(i, 0, signed(v.size()) - 2) {
			int L = v[i] + 1, R = v[i + 1] - 1;
			int mx = (i == 0 ? 0 : a[v[i - 1]]), cnt = 0;
			rep(j, L, R) {
				cnt += (a[j] > mx);
				mx = max(mx, a[j]);
			}
			ans = max(ans, sz - 1 + cnt);
		}
		cout << max(ans, sz) << "\n";
	}
	return 0;
}


