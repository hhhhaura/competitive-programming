#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#pragma GCC target("sse")

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(a) a.begin(), a.end()
#define ceil(a, b) ((a + b - 1) / (b))

using namespace std;

#define int long long int
#define pii pair<int, int>
#define lld long double
#define eps (1e-9)
#define INF 1000000000000000000
#define MOD 1000000007
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<": ", kout("["+string(#a)+"] = ",a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie();
	int t; cin >> t;
	while(t--) {
		int x, y;
		cin >> x >> y;
		int id = max(x, y), cnt = 0;
		if(x == id) cnt = y;
		else cnt = 2 * id - x;
		if(id & 1) cout << (id - 1) * (id - 1) + cnt << "\n";
		else cout << id * id - cnt + 1 << "\n"
		

	}
	return 0;
}

