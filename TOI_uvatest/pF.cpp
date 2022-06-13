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
	int ii = 0, n;
	const int P = 62;
	vector<int> pos(500, -1);
	struct node {
		int cnt;
		vector<int> ch;
	};
	vector<node> v(5000000);
	map<string, int> cnt;
	int get_new() {
		ii ++;
		v[ii].cnt = 0;
		v[ii].ch.assign(P, 0);
		return ii;
	}
	void init_(int _n) {
		ii = -1, n = _n;
		get_new();
		cnt.clear();
		int cur = 0;
		rep(i, 0, 25) pos['a' + i] = cur++;
		rep(i, 0, 25) pos['A' + i] = cur++;
		rep(i, 0, 9) pos['0' + i] = cur++;
	}
	int insert(string s) {
		int len = s.size();
		int cur = 0, ans = 0;
		rep(i, 0, len - 1) {
			int id = pos[s[i]];
			if(!v[cur].ch[id]) v[cur].ch[id] = get_new();
			cur = v[cur].ch[id];
			ans += v[cur].cnt;
			v[cur].cnt ++;
		}
		return ans * 2;
	}
	int solve() {
		int ans = n * (n - 1) / 2;
		vector<string> a(n, "");
		rep(i, 0, n - 1) cin >> a[i];
		sort(all(a), [&](string x, string y) {
			return x.size() < y.size();
		});
		rep(i, 0, n - 1) {
			cnt[a[i]] ++;
			ans += insert(a[i]);
		}
		for(auto i : cnt) {
			ans += i.y * (i.y - 1) / 2;
		}
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, t = 0;
	while(t ++, cin >> n && n) {
		init_(n);
		cout << "Case "<<t<<": "<<solve()<<"\n";
	}

	
	return 0;
}

