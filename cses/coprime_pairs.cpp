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
namespace solver {
	const int P = 1000000;
	vector<int> fac, p, mu, cnt, a;
	void init_() {
		fac.assign(P + 1, 1);
		mu.assign(P + 1, 1);
		cnt.assign(P + 1, 0);
		a.assign(P + 1, 0);
		p.clear();
		rep(i, 2, P) {
			if(fac[i] == 1) {
				p.push_back(i);
				mu[i] = -1;
			}
			for(auto j : p) {
				if(i * j > P) break;
				fac[i * j] = j;
				mu[i * j] = mu[i] * -1;
				if(i % j == 0) {
					mu[i * j] = 0;
					break;
				}
			}
		}
	}
	void solve() {
		rep(i, 1, P) {
			for(int j = i; j <= P; j += i) 
				cnt[i] += a[j];
		}
		int ans = 0;
		rep(i, 1, P) if(cnt[i]) {
			ans += (cnt[i] - 1) * cnt[i] / 2 * mu[i];
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_();
	rep(i, 1, n) {
		int x; cin >> x;
		a[x] ++;
	}
	solve();
	return 0;
}


