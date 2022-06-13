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
	const int P = 1000000;
	vector<int> dp(P + 1, 0);
	rep(i, 3, P) {
		vector<int> cnt(i + 1, 0);
		rep(j, 1, i - 1) if(j != i - j) {
			int val = dp[j] ^ dp[i - j];
			if(val <= i) cnt[val] ++;
		} 
		rep(j, 0, i) if(!cnt[j]) {
			dp[i] = j;
			break;
		}
		if(dp[i] == 0) cerr << i <<", ";
	} 
	cout << "\n";
	return 0;
}


