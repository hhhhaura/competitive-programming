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
random;
signed main() {
	int t; cin >> t;
	auto query = [](int x) {
		string s;
		rep(i, 0, 7) {
			s += char('0' + (x & 1));
			x >>= 1;
		}
		cout << s << endl;
		int ans; cin >> ans;
		if(ans == -1) exit(0);
		return ans;
	};
	while(t--) {
		int cur = query(0);
		while(cur) {
			int num = 0;
			vector<int> v(8, 0);
			iota(all(v), 0);
			shuffle(all(v), rnd);
			rep(i, 0, cur - 1) num |= (1 << v[i]);
			cur = query(num);
		}
	}
	return 0;
}

