#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
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
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, p;
		cin >> n >> p;
		vector<vector<int>> a(n, vector<int>(p, 0));
		rep(i, 0, n - 1) rep(j, 0, p - 1)
			cin >> a[i][j];
		rep(i, 0, n - 1) sort(all(a[i]));
		int ans = 0, pre = 0;
		rep(i, 0, n - 1) {
			if(i & 1) {
				ans += max(0ll, a[i][p - 1] - pre);
				ans += max(a[i][p - 1], pre) - a[i][0];
				pre = a[i][0];
			}
			else {
				ans += max(0ll, pre - a[i][0]);
				ans += a[i][p - 1] - min(pre, a[i][0]);
				pre = a[i][p - 1];
			}
		}
		cout << "Case #" << tt << ": " << ans << "\n";
	}
	
	return 0;
}

