#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define ramdon mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;

#ifdef wiwihorz
#define print(a...) cerr<<__LINE__<<": ",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " ", ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ...e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, cur, ans;
	const int P = 2000000;
	vector<int> cnt;
	vector<vector<pii>> mp;
	void init_(int _n) {
		n = _n, cur = 0, ans = 0;
		cnt.assign(P + 1, 0);
		mp.assign(n + 1, vector<pii>());
	}
	void dfs(int x, int par) {
		ans ^= cur;
		for(auto i : mp[x])  {
			int to = i.first, val = i.second;
			int type = (val > 0 ? 1 : -1), pre = cur;
			val = abs(val);
			cur -= cnt[val] * cnt[val] * val;
			cnt[val] += type;
			cur += cnt[val] * cnt[val] * val;
			dfs(to, x);
			cnt[val] -= type;
			cur = pre;
		}
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	init_(k);
	rep(i, 1, n) {
		int x; cin >> x;
		cnt[x] ++;
	}
	rep(i, 1, P) cur += cnt[i] * cnt[i] * i;
	rep(i, 1, k) {
		int s, x; 
		cin >> s >> x;
		mp[s].push_back({i, x});
	}
	dfs(0, 0);
	cout << ans << "\n";	
	return 0;
}


