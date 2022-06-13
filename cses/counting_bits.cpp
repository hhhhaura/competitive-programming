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
	const int P = 50;
	auto cal = [&](int x) {
		vector<int> dp(P + 1, 0);
		int yes = (n >> x) & 1;
		rrep(i, 0, P - 1) {
			int id = (n >> i) & 1;
			if(x == i && (1 << i) > n) return 0ll;
			if(x != i) {
				dp[i] = (dp[i + 1] * 2);
				if(id && (yes || i > x)) dp[i] += 1;
			}
			else dp[i] = dp[i + 1];
		}
		return (int)(dp[0] + yes);
	};
	int ans = 0;
	rep(i, 0, P - 1) ans = (ans + cal(i));
	cout << ans << "\n";
	return 0;
}


