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
	int n, m; cin >> n;
	string s; cin >> s;
	m = s.size();
	vector<int> pre(m + 1, 0), cur(m + 1, 0);
	cur[0] = 25, cur[1] = 1;
	rep(i, 2, n) {
		pre = cur;
		cur.assign(m + 1, 0);
		rep(j, 0, 0) rep(k, 0, m - 1) 
			cur[j] = (cur[j] + pre[k] * (25 - (s[k] != s[0])) % MOD) % MOD;
		rep(j, 1, 1) rep(k, 0, m - 1) 
			if(!k || s[k] != s[0]) cur[j] = (cur[j] + pre[k]) % MOD;
		rep(j, 2, m - 1) cur[j] = pre[j - 1];
	}
	int ans = 1, val = 0;
	rep(i, 1, n) ans = ans * 26ll % MOD;
	rep(i, 0, m - 1) val = (val + cur[i]) % MOD;
	cout << (ans - val +  MOD) % MOD << "\n";
	return 0;
}


