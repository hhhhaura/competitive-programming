#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define x first
#define y second
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R],++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ...e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<int> ans(1 << n, 0);
	vector<vector<int>> mp(n, vector<int>(n, 0));
	vector<vector<int>> dp(1 << n, vector<int>(n, 0));
	rep(i, 0, n - 1) {
		vector<int> tp(n, 0);
		rep(j, 0, n - 1) cin >> tp[j], tp[j]--;
		rep(j, 0, n - 1) {
			mp[i][tp[j]] = 1;
			if(tp[j] == i) break;
		}
	}
	rep(i, 0, n - 1) dp[1 << i][i] = 1;
	rep(i, 0, (1 << n) - 1) {
		int bg = 31 - __builtin_clz(i);
		rep(j, 0, n - 1) if((i >> j) & 1) {
			rep(k, 0, bg - 1) if(!((i >> k) & 1)) {
				if(mp[j][k]) dp[i ^ (1 << k)][k] += dp[i][j];
			}
			if(mp[j][bg]) ans[i] += dp[i][j];
		}
		rep(j, bg + 1, n - 1) if(!((i >> j) & 1)) 
			dp[i ^ (1 << j)][j] += ans[i];
	}
	ans[0] = 1;
	int m; cin >> m;
	while(m --) {
		string s; cin >> s;
		int cur = 0, mask = (1 << n) - 1;
		rep(i, 0, n - 1) if(s[i] == 'H') cur |= (1 << i);
		cout << ans[cur] * ans[mask ^ cur] << "\n";
	}

	return 0;
}

