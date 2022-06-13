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
	static const int w = 26;
	static const int P = 1000000;
	struct node {
		int par, to, id, tag;
		array<int, w> ch {};
		node() : par(0), to(-1), id(0), tag(0) {}
	};
	int ii = 0;
	vector<node> v{vector<node>(P, node())};
	void insert(string &s, int id) {
		int n = s.size(), cur = 0;
		rep(i, 0, n - 1) {
			int val = s[i] - 'a';
			if(!v[cur].ch[val]) {
				v[cur].ch[val] = ++ii;
				v[ii].par = cur;
			}
			cur = v[cur].ch[val];
			if(i + 1 == n) v[cur].id = id;
		}
	}
	void build() {
		v[0].to = 0;
		queue<int> q;
		rep(i, 0, w - 1) if(v[0].ch[i]) {
			int ch = v[0].ch[i];
			v[ch].to = 0, q.push(ch);
		}
		while(q.size()) {
			int cur = q.front(); q.pop();
			rep(i, 0, w - 1) if(v[cur].ch[i]) {
				int val = v[cur].to, ch = v[cur].ch[i];
				while(val && !v[val].ch[i]) val = v[val].to;
				if(v[val].ch[i]) val = v[val].ch[i];
				v[ch].to = val;
				q.push(ch);
			}
		}
	}
	vector<int> query(int m, string s) {
		vector<int> ans(m + 1, 0);
		int cur = 0, n = s.size();
		rep(i, 0, n - 1) {
			int c = s[i] - 'a';
			while(cur && !v[cur].ch[c]) cur = v[cur].to;
			if(v[cur].ch[c]) cur = v[cur].ch[c];
			int val = cur;
			while(!v[val].tag) {
				v[val].tag = 1;
				ans[v[val].id] = 1;
				val = v[val].to;
			}
		}
		return ans;
	}	
};
namespace solver {
	int n;
	string s;
	AC_automation ac;
	void init_(int _n, string _s) {
		n = _n, s = _s;
	}
	void solve() {
		map<string, int> mp;
		vector<string> v;
		rep(i, 1, n) {
			string a; cin >> a;
			v.push_back(a);
			if(mp.find(a) == mp.end()) {
				ac.insert(a, i);
				mp[a] = i;
			}
		}
		ac.build();
		vector<int> ans = ac.query(n, s);
		rep(i, 0, n - 1) {
			cout << (ans[mp[v[i]]] ? "YES" : "NO") << "\n";
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s; cin >> s;
	int n; cin >> n;
	init_(n, s);
	solve();
	return 0;
}


