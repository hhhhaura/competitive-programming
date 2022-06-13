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
	rep(i, 0, n - 1) {
		vector<int> tp(n, 0);
		rep(j, 0, n - 1) cin >> tp[j], tp[j]--;
		rep(j, 0, n - 1) {
			mp[i][tp[j]] = 1;
			if(tp[j] == i) break;
		}
	}
	auto solve = [&](int mask){
		int sz = __builtin_popcount(mask);
		vector<int> dp(1 << sz, 0);
		vector<vector<int>> tot(sz + 1, vector<int>());
		vector<int> v;
		rep(i, 0, n - 1) if((mask >> i) & 1)
			v.push_back(i);
		rep(i, 0, (1 << sz) - 1) {
			int id = __builtin_popcount(i);
			tot[id].push_back(i);
		}
		dp[0] = 1;
		rep(i, 0, sz - 1) {
			for(auto j : tot[i + 1]) {
				rep(k, 0, sz - 1) if((j >> k) & 1) {
					if(mp[v[i]][v[k]]) dp[j] += dp[j ^ (1 << k)];
				}
			}
		}
		return dp[(1 << sz) - 1];
	};
	rep(i, 0, (1 << n) - 1) ans[i] = solve(i);
	int m; cin >> m;
	while(m --) {
		string s; cin >> s;
		int cur = 0, mask = (1 << n) - 1;
		rep(i, 0, n - 1) if(s[i] == 'H') cur |= (1 << i);
		cout << ans[cur] * ans[mask ^ cur] << "\n";
	}
	return 0;
}

