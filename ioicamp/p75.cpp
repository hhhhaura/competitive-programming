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
struct leechao {
	const int P = 1000000;
	struct segment {
		int m, k;// 小心初始化問題
		int val(int x) {
			return x * m + k;
		}
	};
	int ii;
	vector<int> l, r;
	vector<segment> v;
	void init_() {
		ii = 1;
		l.assign(2 * P, 0);
		r.assign(2 * P, 0);
		v.assign(2 * P, {0, 0});
	}
	void insert(int nd, int L, int R, segment s) {
		if(L == R) {
			if(v[nd].val(L) < s.val(L)) v[nd] = s;
			return;
		}
		int mid = (L + R) / 2;
		if(v[nd].m > s.m) swap(s, v[nd]);
		if(v[nd].val(mid) > s.val(mid)) {
			if(!r[nd]) r[nd] = ++ii; 
			insert(r[nd], mid + 1, R, s);
		}
		else {
			if(!l[nd]) l[nd] = ++ii;
			swap(s, v[nd]);
			insert(l[nd], L, mid, s);
		}
		return;
	} 
	int query(int nd, int L, int R, int x) {
		if(!nd) return 0;
		else if(L == R) return v[nd].val(x);
		else {
			int mid = (L + R) / 2, ans = v[nd].val(x);
			if(x <= mid) return max(query(l[nd], L, mid, x), ans);
			else return max(query(r[nd], mid + 1, R, x), ans);
		}
	}
};

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int q; cin >> q;
	leechao st; st.init_();
	int yes = 0;
	rep(i, 1, q) {
		int tp; cin >> tp;
		if(tp == 0) {
			int a, b;
			cin >> a >> b;
			yes = 1;
			st.insert(1, 1, 1000000, {a, b});
		}
		else {
			int t; cin >> t;
			if(!yes) cout << "empty\n";
			else cout << st.query(1, 1, 1000000, t) << "\n";
		}
	}
	return 0;
}

