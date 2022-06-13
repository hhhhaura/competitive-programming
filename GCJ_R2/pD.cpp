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
	int c;
	vector<pii> a, b;
	void init_(int _c) {
		c = _c;
		a.clear();
		b.clear();
	}
	int cal(int n, vector<pii> &v) {
		vector<int> dp(n + 1, 0), bal(2 * n + 1, -1);
		vector<int> pre[2], dis[2];
		rep(i, 0, 1) {
			pre[i].assign(n + 1, 0);
			dis[i].assign(n + 1, 0);
		}
		rep(i, 1, n) {
			pre[v[i].y][i] += 1;
			dis[v[i].y][i] += v[i].x;
			rep(j, 0, 1) {
				pre[j][i] += pre[j][i - 1];
				dis[j][i] += dis[j][i - 1];
			}
		}
		bal[n] = 0;
		rep(i, 1, n) {
			dp[i] = dp[i - 1] + v[i].x * 2;
			if(i >= 2) dp[i] = min(dp[i], dp[i - 2] 
				+ c * (v[i].y == v[i - 1].y) + v[i].x * 2);
			int cur = pre[0][i] - pre[1][i];
			if(bal[cur + n] != -1) {
				int to = bal[cur + n], id = v[i].y;
				dp[i] = min(dp[i], dp[to] + (dis[id][i] - dis[id][to]) * 2);
			}
			bal[cur + n] = i;
		}
		return dp[n];
	}
	void solve(int t) {
		a.push_back({0, 0});
		b.push_back({0, 0});
		sort(all(a));
		sort(all(b));
		int ans = cal(a.size() - 1, a) + cal(b.size() - 1, b);
		cout << "Case #" << t << ": " << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(i, 1, t) {
		int n, c;
		cin >> n >> c;
		init_(c);
		rep(i, 1, n) {
			int x, s;
			cin >> x >> s;
			if(x < 0) b.push_back({-x, s});
			else a.push_back({x, s});
		}
		solve(i);
	}
	return 0;
}

