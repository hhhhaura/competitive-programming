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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n; cin >> n;
		vector<string> v(n + 1, "");
		vector<int> L(26, 0), R(26, 0);
		vector<int> cnt(26, 0), vis(n + 1, 0);
		rep(i, 1, n) cin >> v[i];
		bool ok = 1;
		rep(i, 1, n) {
			int st = v[i][0] - 'A', yes = 1;
			for(auto j : v[i]) yes &= (st == j - 'A');
			if(yes) cnt[st] += v[i].size(), vis[i] = 1;
			else {
				int l = v[i][0] - 'A';
				int r = v[i].back() - 'A';
				if(L[l]) ok = 0;
				if(R[r]) ok = 0;
				L[l] = i;
				R[r] = i;
			}
		}
		cout << "Case #" << tt << ": ";
		if(!ok) cout << "IMPOSSIBLE\n";
		else {
			string ans = "";
			vector<int> q;
			vis[0] = 1;
			rep(i, 0, 25) if(L[i] && !R[i]) q.push_back(i);
			for(auto i : q) {
				vis[L[i]] = 1;
				rep(j, 1, cnt[i]) ans += char('A' + i);
				ans += v[L[i]];
				cnt[i] = 0;
				int to = v[L[i]].back() - 'A';
				while(!vis[L[to]]) {
					int cur = L[to];
					vis[cur] = 1;
					rep(j, 1, cnt[to]) ans += char('A' + to);
					ans += v[cur];
					cnt[to] = 0;
					to = v[cur].back() - 'A';
				}
				rep(j, 1, cnt[to]) ans += char('A' + to);
				cnt[to] = 0;
			}
			rep(i, 0, 25) rep(j, 1, cnt[i]) ans += char('A' + i);
			rep(i, 1, n) if(!vis[i]) ok = 0;
			vector<int> vv(26, -1);
			rep(i, 0, signed(ans.size()) - 1) {
				int cur = ans[i] - 'A';
				if(vv[cur] == -1) vv[cur] = i;
				else if(vv[cur] + 1 != i) ok = 0;
				vv[cur] = i;
			}
			if(!ok) cout << "IMPOSSIBLE\n";
			else cout << ans << "\n";
		}
		
		
	}
	return 0;
}

