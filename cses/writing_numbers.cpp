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
	auto check = [](int x) {
		int ans = 0, cur = 1;
		while(cur <= x) {
			ans += x / (cur * 10) * cur;
			int val = x % (cur * 10ll);
			ans += max(0ll, min(cur, val - cur + 1));
			cur *= 10ll;
		}
//		int ans1 = 0;
//		rep(i, 1, x) {
//			int cur = i;
//			while(cur) {
//				ans1 += (cur % 10 == 1);
//				cur /= 10;
//			}
//		}
//		print(x, ans, ans1);
		return ans;
	};
	int L = 1, R = INF + 1;
	while(R - L > 1) {
		int mid = (L + R) / 2;
		if(check(mid) <= n) L = mid;
		else R = mid;
	}
	cout << L << "\n";
	return 0;
}


