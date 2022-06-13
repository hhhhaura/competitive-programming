#define wiwihorz
#include <bits/stdc++.h>
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
#define print(a...) cerr<<"LINE"<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() {cerr << endl;}
template<class T1, class ...T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<int> a;
	vector<vector<int>> mp = {
		{16, 22, 18, 25},
		{21, 6, 7, 13}, 
		{23, 3, 5, 21},
		{18, 4, 17, 5, 2, 23},
		{22, 18, 3, 17},
		{3, 17, 19, 6, 2, 21},
		{5, 19, 24, 7, 1, 21},
		{6, 24, 20, 9, 13, 1},
		{20, 9, 10, 14},
		{7, 20, 8, 10, 12, 13},
		{9, 8, 14, 11, 12},
		{10, 14, 15},
		{13, 9, 10},
		{1, 7, 9, 12},
		{8, 10, 11, 15},
		{14, 11},
		{0, 22},
		{4, 3, 5, 19},
		{0, 22, 4, 3, 23, 25},
		{17, 5, 6, 24},
		{24, 7, 9, 8},
		{2, 5, 6, 1},
		{16, 0, 18, 4},
		{25, 18, 3, 2},
		{19, 6, 7, 20},
		{0, 18, 23}
	};
	struct node {int L, R, id, st; };
	vector<bool> vis[26][26];
	void init_(int _n, string s) {
		n = _n;
		a.assign(n + 1, 0);
		rep(i, 0, n - 1) a[i + 1] = s[i] - 'A';
		rep(i, 0, 25) rep(j, 0, 25) vis[i][j].assign(n + 1, 0);
	}
	int solve() {
		deque<node> q;
		q.push_back({5, 9, 0, 0});
		vis[5][9][0] = 1;
		while(q.size()) {
			node cur = q.front(); q.pop_front();
			int st = cur.st, to = a[cur.id + 1];
			int L = cur.L, R = cur.R, id = cur.id;
			if(id == n) return st;
			for(auto i : mp[cur.L]) {
				node nxt = {i, R, id + (i == to), st + 1};
				if(vis[nxt.L][nxt.R][nxt.id]) continue;
				vis[nxt.L][nxt.R][nxt.id] = 1;
				q.push_back(nxt);
			}
			node nxt = {L, R, id + (to == L), st};
			if(!vis[nxt.L][nxt.R][nxt.id]) {
				vis[nxt.L][nxt.R][nxt.id] = 1;
				q.push_front(nxt);
			}
			nxt = {L, R, id + (to == R), st};
			if(!vis[nxt.L][nxt.R][nxt.id]) {
				vis[nxt.L][nxt.R][nxt.id] = 1;
				q.push_front(nxt);
			}
			for(auto i : mp[cur.R]) {
				node nxt = {L, i, id + (i == to), st + 1};
				if(vis[nxt.L][nxt.R][nxt.id]) continue;
				vis[nxt.L][nxt.R][nxt.id] = 1;
				q.push_back(nxt);
			}
		}
		
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	string s; cin >> s;
	init_(n, s);
	cout << solve() << "\n";
	return 0;
}


