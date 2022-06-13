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
	string s; cin >> s;
	int n = s.size();
	const int w = 37;
	vector<int> pre(2 * n + 1, 0), inv(2 * n + 1, 0);
	int cur = 1;
	auto pow_ = [](int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	auto comp = [&](int a, int b) {
		int L = 0, R = n + 1;
		while(R - L > 1) {
			int mid = (L + R) / 2;
			int aa = (pre[a + mid - 1] - pre[a - 1]) * inv[a] % MOD;
			aa = (aa + MOD) % MOD;
			int bb = (pre[b + mid - 1] - pre[b - 1]) * inv[b] % MOD;
			bb = (bb + MOD) % MOD;
			if(aa == bb) L = mid;
			else R = mid;
		}
		return (s[(a + L - 1) % n] < s[(b + L - 1) % n]);
	};
	rep(i, 1, 2 * n) {
		pre[i] = (pre[i - 1] + cur * (s[(i - 1) % n] - 'a' + 1) % MOD) % MOD;
		inv[i] = pow_(cur, MOD - 2);
		cur = cur * w % MOD;
	}
	int id = 1;
	rep(i, 2, n) id = (comp(id, i) ? id : i);
	string ans;
	rep(i, id, id + n - 1) ans += s[(i - 1) % n];
	cout << ans << "\n";
	return 0;
}


