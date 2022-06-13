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
#define x first
#define y second
namespace solver {
	int n, a, b, ans;
	vector<pii> v;
	set<pii> al, ar, bl, br;
	void init_(int _n, int _a, int _b) {
		ans = 0;
		n = _n, a = _a, b = _b;
		v.assign(n, {0, 0});
	}
	void maintain(set<pii> &L, set<pii> &R, int tot) {
		while(R.size() < tot) {
			auto it = L.begin();
			ans -= it->x;
			R.insert({it->x, it->y});
			L.erase(it);
		}
		while(R.size() > tot) {
			auto it = prev(R.end());
			ans += it->x;
			L.insert({it->x, it->y});
			R.erase(it);
		}
		return;
	}
	void solve() {
		sort(all(v), [](pii a, pii b) {
			return a.x > b.x;
		});
		ans = 0;
		int tot = 0;
		rep(i, 0, a - 1) {
			al.insert({v[i].x - v[i].y, i});
			ans += v[i].x;
		}
		rep(i, a, n - 1) {
			br.insert({-v[i].y, i});
			ans += v[i].y;
		}
		maintain(bl, br, b);
		int best = ans;
		
		if(a) rep(i, a, a + b - 1) {
			tot = min(tot + 1, b);
			if(bl.find({-v[i].y, i}) != bl.end()) {
				bl.erase(bl.find({-v[i].y, i}));
			}
			else {
				br.erase(br.find({-v[i].y, i}));
				ans -= v[i].y;
			}
			maintain(bl, br, b - tot);
			ans += v[i].x;
			maintain(al, ar, tot);
			best = max(ans, best);
			ans += v[i].y - v[i].x;
			ar.insert({v[i].x - v[i].y, i});
			maintain(al, ar, tot);
		}
		cout << best << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int a, b, n;
	cin >> a >> b >> n;
	init_(n, a, b);
	rep(i, 0, n - 1) cin >> v[i].x >> v[i].y;
	solve();
	return 0;
}


