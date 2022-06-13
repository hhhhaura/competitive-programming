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
struct AC_automation {
	int ii = 0;
	static const int P = 1000000;
	struct node {
		int to = -1, id = 0, tag = INF, cnt = 0;
		array<int, 26> ch{};
	};
	vector<node> v{vector<node>(P, node())};
	void insert(int id, string s) {
		int n = s.size(), cur = 0;
		rep(i, 0, n - 1) {
			int val = s[i] - 'a';
			if(!v[cur].ch[val]) v[cur].ch[val] = ++ii;
			cur = v[cur].ch[val];
		}
		v[cur].id = id;
	}
	void build() {
		 v[0].to = 0;
		 queue<int> q;
		 rep(i, 0, 25) if(v[0].ch[i]) {
		 	int cur = v[0].ch[i];
			v[cur].to = 0;
			q.push(cur);
		 }
		 while(q.size()) {
		 	int cur = q.front(); q.pop();
			rep(i, 0, 25) if(v[cur].ch[i]) {
				int par = v[cur].to, val = v[cur].ch[i];
				while(par && !v[par].ch[i]) par = v[par].to;
				if(v[par].ch[i]) par = v[par].ch[i];
				q.push(val);
				v[val].to = par;
				v[par].cnt++;
			}
		 }
	}
	vector<int> query(string s, int m) {
		int n = s.size(), cur = 0;
		vector<int> ans(m + 1, 0);
		rep(i, 0, n - 1) {
			int val = s[i] - 'a';
			while(cur && !v[cur].ch[val]) cur = v[cur].to;
			if(v[cur].ch[val]) {
				cur = v[cur].ch[val];
				v[cur].tag = min(v[cur].tag, i);
			}
		}
		queue<int> q;
		rep(i, 1, ii) if(!v[i].cnt) q.push(i);
		while(q.size()) {
			int cur = q.front(); q.pop();
			int par = v[cur].to;
			ans[v[cur].id] = v[cur].tag;
			v[par].tag = min(v[par].tag, v[cur].tag);
			if(!--v[par].cnt) q.push(par);
		}
		return ans;
	}
};
namespace solver {
	string s;
	int n;
	vector<string> a;
	map<string, int> mp;
	AC_automation ac;
	void init_(string _s, int _n) {
		n = _n, s = _s;
		a.assign(n + 1, "");
	} 
	void solve() {
		rep(i, 1, n) {
			if(mp.find(a[i]) == mp.end()) {
				mp[a[i]] = i;
				ac.insert(i, a[i]);
			}
		}
		ac.build();
		vector<int> v = ac.query(s, n);
		rep(i, 1, n) {
			int ans = v[mp[a[i]]];
			if(ans == INF) cout << "-1\n";
			else cout << (ans - signed(a[i].size()) + 2) << "\n";
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s; cin >> s;
	int n; cin >> n;
	init_(s, n);
	rep(i, 1, n) cin >> a[i];
	solve();
	return 0;
}


