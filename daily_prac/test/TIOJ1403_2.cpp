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

#define INF 1000000
#define MOD 1000000007
#define eps (1e-15)
#define lld double
#define int long long
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
#define pll pair<lld, lld>
namespace solver {
	int n;
	vector<int> x, s, v, pos;
	void init_(int _n) {
		n = _n;
		pos.assign(n + 2, 0);
		iota(all(pos), 0);
		x.assign(n + 2, 0);
		s.assign(n + 2, INF);
		v.assign(n + 2, 0);
	}
	struct comp {
		bool operator()(pair<pll, int> a, pair<pll, int> b) {
			if(abs(a.x.x - b.x.x) <= eps) return a.x.y > b.x.y;
			else return a.x.x > b.x.x;
		}
	};
	int lowbit(int x) {
		return x & -x;
	}
	void modify(int x, int val) {
		for(int i = x; i <= n; i += lowbit(i)) {
			v[i] += val;
		}
	}
	int query(int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += v[i];
		}
		return ans;
	}
	int calculate(int t) {
		vector<pii> tp;
		rep(i, 1, n) {
			int to = x[i] + t * s[i];
			tp.push_back({to, i});
		}
		sort(all(tp));
		int ans = 0;
		rep(i, 0, n - 1) {	
			int id = tp[i].y;
			ans += query(n - id + 1);
			modify(n - id + 1, 1);
		}
		return ans;
	}
	void solve() {
		int ans = calculate(INF + 1);
		set<pii> ss;
		priority_queue<pair<pll, int>, 
			vector<pair<pll, int>>, comp> q;
		rep(i, 0, n + 1) ss.insert({i, i});
		set<pii> rec;
		rep(i, 1, n - 1) if(s[i] > s[i + 1]){
			lld t = (lld)(x[i + 1] - x[i]) / (s[i] - s[i + 1]);
			q.push({{t, x[i] + t * s[i]}, i});
			rec.insert({i, i + 1});
		}
		cout << ans % INF << "\n";
		rep(i, 1, min(10000ll, ans)) {
			if(!q.size()) while(1);
			pair<pll, int> p = q.top(); q.pop();
			int cur = p.y;
			auto L = prev(ss.find({pos[cur], cur}));
			auto R = next(ss.find({pos[cur], cur}));
			int nxt = R->y, pre = L->y;
			cout << cur << " " << nxt << "\n";
			if(pre && s[pre] > s[nxt]) {
				lld t = (lld)(x[nxt] - x[pre]) / (s[pre] - s[nxt]);
				if(rec.find({pre, nxt}) == rec.end()) {
					q.push({{t, x[pre] + t * s[pre]}, pre});
					rec.insert({pre, nxt});
				}	
			}
			if(next(R)->y != n + 1 && s[next(R)->y] < s[cur]) {
				int tar = next(R)->y;
				lld t = (lld)(x[tar] - x[cur]) / (s[cur] - s[tar]);
				if(rec.find({cur, tar}) == rec.end()) {
					q.push({{t, x[cur] + t * s[cur]}, cur});
					rec.insert({cur, tar});
				}
			}
			ss.erase(R);
			ss.erase(ss.find({pos[cur], cur}));
			swap(pos[cur], pos[nxt]);
			ss.insert({pos[cur], cur});
			ss.insert({pos[nxt], nxt});
		} 
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	cerr << fixed << setprecision(17);
	init_(n);
	rep(i, 1, n) cin >> x[i] >> s[i];
	solve();
	return 0;
}




