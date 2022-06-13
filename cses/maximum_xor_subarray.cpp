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
	int ii;
	const int P = 32;
	struct node { int z, o, cnt; };
	vector<node> v(10000000, {0, 0, 0});
	void insert(int x) {
		int cur = 1;
		rrep(i, 0, P) {
			int to = (x >> i) & 1;
			v[cur].cnt ++;
			if(to) {
				if(!v[cur].o) v[cur].o = ++ii;
				cur = v[cur].o;
			}
			else {
				if(!v[cur].z) v[cur].z = ++ii;
				cur = v[cur].z;
			}
		}
		v[cur].cnt ++;
	}
	int query(int x) {
		int cur = 1, ans = 0;
		rrep(i, 0, P) {
			int to = (x >> i) & 1, val = 0;
			int L = v[cur].z, R = v[cur].o;
			if(to && v[L].cnt || !v[R].cnt) cur = L;
			else cur = R, val = 1;
			ans |= (val << i);
		}
		return ans ^ x;	
	}
	void solve(int n) {
		ii = 1;
		int cur = 0, ans = 0;
		insert(0);
		rep(i, 1, n) {
			int x; cin >> x;
			cur ^= x;
			ans = max(ans, query(cur));
			insert(cur);
		}
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	solve(n);
	return 0;
}


