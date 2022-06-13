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
const int P = 60;
map<pair<int, vector<int>>, int> mp;
int solve(int x, vector<int> v) {
	if(mp.find({x, v}) != mp.end()) return mp[{x, v}];
	vector<int> cnt(x + 1, 0);
	rep(i, 1, x) {
		int no = 0;
		rep(j, 0, signed(v.size()) - 1) 
			if(v[j] == i) no = 1;
		if(!no) {
			v.push_back(i);
			int ans = solve(x - i, v);
			if(ans <= x) cnt[ans] ++;
			v.pop_back();
		}
	}
	rep(i, 0, x) if(!cnt[i]) return mp[{x, v}] = i;
}
signed main() {
	cerr << "0, ";
	rep(i, 1, P) cerr << solve(i, vector<int>()) << ", ";
	cerr << "\n";
	return 0;
}


