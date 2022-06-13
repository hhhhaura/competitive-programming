#define wiwihorz
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
#define x first
#define y second
namespace solver {
	vector<pair<pii, pii>> v;
	multiset<pii> s;
	void solve() {
		sort(all(v));
		int ans = 0;
		for(auto i : v) {
			int tp = i.x.y, h = i.y.x, num = i.y.y;
			if(tp == 1) s.insert({h, num});
			else {
				int cnt = 0;
				auto it = s.lower_bound({h, -INF});
				while(it != s.end()) {
					int mn = min(num, it -> y);
					num -= mn, ans += mn;
					auto tp = it;
					it = next(it);
					if(!num) {
						s.insert({tp->x, tp->y - mn});
						s.erase(tp);
						break;
					}
					s.erase(tp);
				}
			}
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	while(n--) {
		int q, t, x, num;
		cin >> q >> t >> x >> num;
		int a = -x + t, b = -x - t;
		v.push_back({{a, q}, {b, num}});
	}
	solve();
	return 0;
}

