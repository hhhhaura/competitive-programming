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
	int n;
	const int k = 32;
	vector<vector<int>> dis;
	vector<vector<pii>> mp;
	vector<int> sz, mx, vis, sum, cnt, minu, a, ac;
	void init_(int _n) {
		n = _n;
		dis.assign(k + 1, vector<int>(n + 1, 0));
		mp.assign(n + 1, vector<pii>());
		sz.assign(n + 1, 0), mx.assign(n + 1, 0);
		vis.assign(n + 1, 0), sum.assign(n + 1, 0);
		cnt.assign(n + 1, 0), minu.assign(n + 1, 0);
		a.assign(n + 1, 0), ac.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) if(i.first != par) {
			if(vis[i.first]) continue;
			get_sz(i.first, x);
			sz[x] += sz[i.first];
			mx[x] = max(mx[x], sz[i.first]);
		}
	}
	int get_cen(int x, int par, int tot) {
		int best = x;
		for(auto i : mp[x]) if(i.first != par) {
			if(vis[i.first]) continue;
			int cur = get_cen(i.first, x, tot);
			if(max(tot - sz[best], mx[best]) > 
				max(tot - sz[cur], mx[cur])) best = cur;
		}
		return best;
	}
	void get_dis(int x, int par, int top, int cur) {
		dis[top][x] = cur;
		for(auto i : mp[x]) if(i.first != par) {
			if(vis[i.first]) continue;
			get_dis(i.first, x, top, cur + i.second);
		}
	}
	void deco(int x, int par, int dep) {
		get_sz(x, x);
		int cen = get_cen(x, x, sz[x]);
		vis[cen] = dep, ac[cen] = par;
		get_dis(cen, cen, dep, 0);
		for(auto i : mp[cen]) if(!vis[i.first]) {
			deco(i.first, cen, dep + 1);
		}
	}
	void modify(int x) {
		if(a[x]) return;
		int cur = x, dep = vis[x];
		a[x] = 1;
		while(cur != 0) {
			sum[cur] += dis[dep][x], cnt[cur] += 1;
			minu[cur] += dis[dep - 1][x];
			dep --, cur = ac[cur];
		}
	}
	int query(int x) {
		int ans = sum[x];
		int dep = vis[x], cur = x;
		while(ac[cur] != 0) {
			int par = ac[cur];
			ans += sum[par] - minu[cur]
				+ dis[dep - 1][x] * (cnt[par] - cnt[cur]);
			cur = par, dep --;
		}
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; 
	cin >> n >> q;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b, c;
		cin >> a >> b >> c;
		a++, b++;
		mp[a].push_back({b, c});
		mp[b].push_back({a, c});
	}
	deco(1, 0, 1);
	rep(i, 1, q) {
		int tp, x;
		cin >> tp >> x;
		x++;
		if(tp == 1) modify(x);
		else cout << query(x) << "\n";
	}
	return 0;

}

