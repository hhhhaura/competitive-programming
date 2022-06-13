#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
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
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout(){cerr<< endl;}
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n;
	vector<vector<int>> mp;
	vector<int> dep, mn, mx, a, dp, pre, len;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		pre.assign(n + 1, 0);
		len.assign(n + 1, 0);
		dep.assign(n + 1, INF);
		mn.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		a.assign(n + 1, 0);
		dp.assign(n + 1, 0);
	}
	void dfs(int x, int par, int d) {
		dep[x] = d;
		if(a[x]) mn[x] = x;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x, d + 1);
			if(dep[mn[x]] > dep[mn[i]]) mn[x] = mn[i];
		}
	}
	void dfs1(int x, int par, int top) {
		int v1 = top, v2 = 0;
		auto dis = [&](int a, int b) {
			if(dep[a] > dep[b]) swap(a, b);
			if(dep[a] < dep[x]) return dep[b] - dep[a];
			else return dep[a] + dep[b] - 2 * dep[x];
		};
		if(dis(mn[x], x) > dis(top, x)) len[x] = dep[x] - dep[gt];
		len[x] = dis(x, mn[x]);
		if(a[x]) v1 = x;
		for(auto i : mp[x]) if(i != par) {
			int cur = mn[i];
			if(dis(cur, x) < dis(v1, x)) swap(v1, cur);
			if(dis(cur, x) < dis(v2, x)) swap(v2, cur);
		}
		for(auto i : mp[x]) if(i != par) {
			if(mn[i] == v1) dfs1(i, x, v2);
			else dfs1(i, x, v1);
		}
	}
	void solve(int x, int par) {
		for(auto i : mp[x]) if(i != par) solve(i, x);
		if(a[x]) {
			pre[x] = 1;
			for(auto i : mp[x]) 
				if(i != par) dp[x] += dp[i];
			dp[x] += 1, mx[x] = 0;
			return;
		}
		vector<pii> ans;
		// dp4
		int val = 0, m = 0;
		for(auto i : mp[x]) if(i != par) {
			val += dp[i];
			m = max(m, mx[i] - 1);
		}
		ans.push_back({val, m});
		// dp3
		val = 0, m = 0;
		for(auto i : mp[x]) if(i != par) {
			if(len[x] == dep[mn[i]])
		}
	}
	void trace() {
	
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);

	return 0;
}


