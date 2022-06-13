#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, m;
	struct edge { int u, v, d; };
	vector<vector<pii>> mp;
	vector<pair<int, edge>> a;
	vector<int> v, tot, dp;
	vector<vector<edge>> es;
	void init_(int _n) {
		n = _n;
		dp.assign(n + 1, INF);
		mp.assign(n + 1, vector<pii>());
		a.clear();
		v.clear();
		tot.clear();
		es.clear();
	}
	
	void solve() {
		sort(all(v));
		v.resize(unique(all(v)) - v.begin());
		m = v.size();
		es.assign(m + 1, vector<edge>());
		for(auto i : a) {
			int id = lower_bound(all(v), i.x) - v.begin() + 1;
			es[id].push_back(i.y);
		}
		dp[1] = 0;
		auto operate = [&]() {
			priority_queue<pii, vector<pii>, greater<pii>> q;
			for(auto i : tot) q.push({dp[i], i});
			while(q.size()) {
				pii p = q.top(); q.pop();
				if(p.x != dp[p.y]) continue;
				int cur = p.y;
				for(auto i : mp[cur]) {
					int v = dp[cur] + i.y;
					if(v < dp[i.x]) {
						dp[i.x] = v;
						q.push({dp[i.x], i.x});
					}
				}
			}
			for(auto i : tot) mp[i].clear();
		};
		rrep(i, 1, m) {
			tot.clear();
			for(auto j : es[i]) {
				tot.push_back(j.u);
				tot.push_back(j.v);
				mp[j.u].push_back({j.v, j.d});
				mp[j.v].push_back({j.u, j.d});
			}
			sort(all(tot));
			tot.resize(unique(all(tot)) - tot.begin());
			operate();
		}
		cout << dp[n] << "\n";
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int x, y, h, d;
		cin >> x >> y >> h >> d;
		v.push_back(h);
		a.push_back({h, {x, y, d}});
	}
	solve();
	return 0;
}


