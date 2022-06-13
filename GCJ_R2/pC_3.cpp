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
#define INF 9000000000000000000
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
	int n, ii;
	vector<pii> a, b;
	vector<int> my, mx, vis, piv, kid;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n, ii = 0;
		a.assign(n + 1, {0, 0});
		b.assign(n + 1, {0, 0});
		my.assign(n + 1, -1);
		mx.assign(n + 1, -1);
		vis.assign(n + 1, 0);
		piv.assign(n + 1, 0);
		kid.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
	}
	int dis(pii a, pii b) {
		pii c = {a.x - b.x, a.y - b.y};
		return c.x * c.x + c.y * c.y;
	}
	bool dfs(int x) {
		for(auto i : mp[x]) {
			if(vis[i] == ii) continue;
			vis[i] = ii;
			if(my[i] == -1 || dfs(my[i])) {
				my[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int find_close() {
		rep(i, 1, n) if(vis[i] != ii){
			int to = my[i];
			if(mp[to][piv[to]] == i) return i;
		}
		return -1;
	}
	void reverse(int x) {
		vector<int> use(n + 1, 0);
		vector<int> pre(n + 1, 0);
		vector<int> to(n + 1, 0);
		rep(i, 1, n) to[i] = mp[i][piv[i]];
		int cur = x;
		while(!use[to[cur]]) {
			use[to[cur]] = 1;
			pre[to[cur]] = cur; 
			cur = my[to[cur]];
		}
		int tp = my[to[cur]];
		pre[to[cur]] = cur;
		cur = to[cur];
		while(true) {
			int per = pre[cur], nxt = mx[per];
			mx[per] = cur;
			my[cur] = per;
			if(per == tp) break; 
			cur = nxt;
		}
	}
	void solve(int t) {
		rep(i, 1, n) {
			int zero = dis(b[0], a[i]);
			rep(j, 1, n) {
				if(dis(b[j], a[i]) <= zero) 
					mp[i].push_back(j);
			}
			sort(all(mp[i]), [&](int x, int y) {
				return dis(a[i], b[x]) < dis(a[i], b[y]);
			});
		}
		int cnt = 0;
		rep(i, 1, n) ii++, cnt += dfs(i);
		cout << "Case #" << t << ": ";
		if(cnt != n) cout << "IMPOSSIBLE\n";
		else {
			cout << "POSSIBLE\n", ii++;
			rep(i, 1, n) {
				rep(j, 1, n) if(!kid[j]) {
					while(vis[mp[j][piv[j]]] == ii) piv[j] ++;
				}
				int pos = find_close();
				if(pos == -1) {
					rep(j, 1, n) if(!kid[j]) reverse(j);
					pos = find_close();
					assert(pos != -1);
				}
				cout << my[pos] << " " << pos + 1 << "\n";
				vis[pos] = ii;
				kid[my[pos]] = 1;
			}
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> a[i].x >> a[i].y;
		rep(i, 0, n) cin >> b[i].x >> b[i].y;
		solve(tt);
	}
	return 0;
}

