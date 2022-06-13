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
	int t; cin >> t;
	const int P = 31;
	while(t--) {
		int n, k; 
		cin >> n >> k;
		int pre = 0, tot = 0;
		vector<int> st(P + 1, 0);
		auto cal_pre = [&](int x, int id) {
			int ans = 0;
			rep(i, 1, id) {
				int len = (1ll << i);
				if(x >= st[i]) ans += (x - st[i]) / len + 1;
			}
			return ans;
		};
		auto bins = [&](int x, int id) {
			int L = 0, R = n + 1;
			while(R - L > 1) {
				int mid = (L + R) / 2;
				if(mid - cal_pre(mid, id - 1) >= x) R = mid;
				else L = mid;
			}
			return R;
		};
		rep(i, 1, P) {
			int len = (1ll << i);
			int cur = bins((tot + 1 == n ? 1ll : 2 - pre), i);
			int cnt = (n - cur) / len + 1;
			if(tot + cnt >= k) {
				cout << cur + (k - tot - 1) * len << "\n";
				break;
			}
			st[i] = cur, tot += cnt;
			int last = cur + (cnt - 1) * len;
			pre = (n - cal_pre(n, i)) - (last - cal_pre(last, i));
		}
	}
	return 0;
}


