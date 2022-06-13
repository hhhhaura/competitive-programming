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
	while(t--) {
		int n; cin >> n;
		int tot = 0;
		vector<int> v(n + 1, 0);
		rep(i, 1, n) {
			cin >> v[i];
			tot += v[i];
		}
		const int P = 45001;
		vector<bitset<P>> cur(n + 1, bitset<P>()), nxt;
		cur[0][0] = 1;
		rep(i, 1, n) {
			nxt.assign(n + 1, bitset<P>());
			rep(j, 0, i) {
				if(j) nxt[j] |= cur[j - 1] << v[i];
				nxt[j] |= cur[j];
			} 
			cur = nxt;
		}
		int best = 0, h = n / 2;
		rep(i, 0, tot) {
			if(cur[h][i] && cur[n - h][tot - i]) {
				if(abs(best - (tot - best)) >= abs(i - (tot - i))) {
					best = i;
				}
			}
		}
		int L = best, R = tot - best;
		if(L > R) swap(L, R);
		cout << L << " " << R << "\n";
		if(t) cout << endl;
		
	}
	return 0;
}

