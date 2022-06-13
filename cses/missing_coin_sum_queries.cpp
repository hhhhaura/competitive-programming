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
#define x first
#define y second
namespace solver {
	int n, q, sz = 632;
	const int P = 30;
	struct query { int l, r, id; };
	vector<int> ans, a, sum;
	vector<query> v;
	vector<multiset<int>> s;
	void init_(int _n, int _q) {
		n = _n, q = _q;
		s.assign(P + 1, multiset<int>());
		ans.assign(q + 1, 0);
		a.assign(n + 1, 0);
		sum.assign(P + 1, 0);
		v.clear();
	}
	void add(int x) {
		int pos = 31 - __builtin_clz(x);
		sum[pos] += x;
		s[pos].insert(x);
	}
	void minu(int x) {
		int pos = 31 - __builtin_clz(x);
		sum[pos] -= x;
		s[pos].erase(s[pos].find(x));
	}
	void solve() {
		sort(all(v), [&](query a, query b) {
			int A = a.l / sz, B = b.l / sz;
			if(A == B) return a.r < b.r;
			else return A < B;
		});
		int l = 1, r = 0;
		for(auto i : v) {
			while(r < i.r) add(a[++r]);
			while(l > i.l) add(a[--l]);
			while(l < i.l) minu(a[l++]);
			while(r > i.r) minu(a[r--]);
			int cur = 0;
			rep(j, 0, P) if(sum[j]) {
				auto it = s[j].begin();
				if(cur >= *it - 1) cur += sum[j];
			}
			ans[i.id] = cur + 1;
		}
		rep(i, 1, q) cout << ans[i] << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n, q);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, q) {
		int l, r; 
		cin >> l >> r;
		v.push_back({l, r, i});
	}
	solve();
	return 0;
}


