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
namespace solver {
	int n, ii;
	const int P = 100000;
	vector<vector<int>> mp(P);
	struct node {
		int p = -1;
		array<int, 3> to = {};
		array<int, 3> dp = {};
	};
	vector<int> id;
	vector<node> v(P);
	vector<vector<int>> a;
	void init_() {
		ii = 1;
		id.assign(200, 0);
		id['r'] = 0;
		id['g'] = 1;
		id['b'] = 2;
	}
	void insert(string s, int w) {
		int cur = 1, n = s.size();
		rep(i, 0, n - 1) {
			print(i, cur);
			int val = id[s[i]];
			if(!v[cur].to[val]) v[cur].to[val] = ++ii;
			if(i == n - 1) v[cur].dp[val] += w;
			cur = v[cur].to[val];
		}
		return;
	}
	void dfs(int x, vector<int> tot) {
		rep(i, 0, 2) {
			v[x].dp[i] += tot[i];
			tot[i] = v[x].dp[i];
		}
		print(x);
		vprint(all(tot));
		for(auto i : mp[x]) dfs(i, tot);
	}
	void build() {
		queue<int> q;
		v[1].p = 0;
		mp[0].push_back(1);
		rep(i, 0, 2) if(v[1].to[i]) {
			int val = v[1].to[i];
			v[val].p = 0;
			mp[0].push_back(val);
			q.push(val);
		}	
		while(q.size()) {
			int cur = q.front(); q.pop();
			print(cur);
			rep(i, 0, 2) if(v[cur].to[i]) {
				int val = v[cur].p, id = v[cur].to[i];
				while(val && !v[val].to[i]) val = v[val].p;
				if(v[val].to[i]) val = v[val].to[i];
				print(id, val);
				v[id].p = val;
				mp[val].push_back(id);
				q.push(id);
			}
		}
		dfs(0, {0, 0, 0});
	}
	void solve(string s) {
		int n = s.size();
		a.assign(n + 1, vector<int>(ii + 1, -INF));
		rep(i, 0, ii) a[n][i] = 0;
		rep(i, 0, n) a[i][0] = 0;
		rrep(i, 0, n - 1) rep(j, 0, ii) {
			int val = id[s[i]];
			if(s[i] == 'x') {
				rep(k, 0, 2) {
					int gogo = j;
					while(gogo && !v[gogo].to[k]) gogo = v[gogo].p;
					if(v[gogo].to[k]) gogo = v[gogo].to[k];
					else gogo = 1;
					a[i][j] = max(a[i][j], a[i + 1][gogo] + v[j].dp[k]);
				}
			}
			else {
				int gogo = j;
				while(gogo && !v[gogo].to[val]) gogo = v[gogo].p;
				if(v[gogo].to[val]) gogo = v[gogo].to[val];
				else gogo = 1;
				a[i][j] = max(a[i][j], a[i + 1][gogo] + v[j].dp[val]);
			}
			print(i, j, a[i][j]);
		}
		cout << a[0][1] << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_();
	rep(i, 1, k) {
		string s; cin >> s;
		int w; cin >> w;
		insert(s, w);
	}
	build();
	string s; cin >> s;
	solve(s);
	return 0;
}

/*
7 3
r 1
g 1
rgr 3
rgrrrgr
*/
