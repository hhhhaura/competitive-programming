#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__, kout("["+string(#a)+"] = ", a)
void kout() { cerr << endl; }
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);

	return 0;
}

