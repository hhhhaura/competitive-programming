#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 9000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() {cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second 
namespace solver {
	vector<pii> a;
	set<pii> X, Y;
	int n;
	int dis(pii a, pii b) {
		pii c = {a.x - b.x, a.y - b.y};
		return c.x * c.x + c.y * c.y;
	}
	int solve() {
		sort(all(a));
		int cur = INF;
		for(auto i : a) {
			while(X.size() && (i.x - X.begin() -> first) 
				* (i.x - X.begin() -> first)>= cur) {
				pii b = *X.begin();
				X.erase(X.find({b.x, b.y}));
				Y.erase(Y.find({b.y, b.x}));				
			}
			X.insert({i.x, i.y});
			Y.insert({i.y, i.x});
			auto it = Y.find({i.y, i.x});
			auto R = it, L = it;
			for(int cnt = 0; cnt < 2; cnt ++) {
				R = next(R);
				if(R == Y.end()) break;
				cur = min(cur, dis(*R, {i.y, i.x}));
			}
			for(int cnt = 0; cnt < 2; cnt ++) {
				if(L == Y.begin()) break;
				L = prev(L);
				cur = min(cur, dis(*L, {i.y, i.x}));
			}
		}
		return cur;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	rep(i, 0, n - 1) {
		int x, y; cin >> x >> y;
		a.push_back({x, y});
	}
	cout << solve() << "\n";
	return 0;
}
