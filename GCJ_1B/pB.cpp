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
		int n, p;
		cin >> n >> p;
		vector<vector<int>> a(n + 1, vector<int>(p, 0));
		vector<int> cur, nxt;
		vector<vector<int>> dp(n + 1, vector<int>(p, INF));
		rep(i, 1, n) rep(j, 0, p - 1) cin >> a[i][j];
		rep(i, 1, n) sort(all(a[i]));
		cur.assign(p, INF);
		cur[0] = 0;
		rep(i, 1, n) {
			int mn = a[i][0], mx = a[i][p - 1];
			vector<int> v = a[i - 1];
			nxt.assign(p, INF);
			rep(j, 1, p - 2) {
				int end = a[i][j];
				rep(k, 0, p - 1) {
					int val = v[k];
					if(val <= mx && val >= mn) {
						int best = min(val - end, end - val) + (mx - mn) * 2;
						nxt[j] = min(nxt[j], cur[k] + best);
					}
					else if(val > mx) nxt[j] = min(nxt[j], cur[k]+val-mn * 2 +end);
					else nxt[j] = min(nxt[j], cur[k] + mx - val + mx - end);
				}
			}
			rep(j, 0, 0) rep(k, 0, p - 1) {
				int val = a[i - 1][k], end = mn;
				if(val <= mx && val >= mn) nxt[j] = min(nxt[j],cur[k]+mx*2-val-mn);
				else if(val > mx) nxt[j] = min(nxt[j],cur[k]+val-mn+end - mn);
				else nxt[j] = min(nxt[j], cur[k] + mx - val + mx - end);
			}
			rep(j, p - 1, p - 1) rep(k, 0, p - 1) {
				int val = a[i - 1][k], end = mx;
				if(val <= mx && val >= mn) nxt[j]=min(nxt[j],cur[k] + val+mx-mn*2);
				else if(val > mx) nxt[j] = min(nxt[j], cur[k] + val-mn*2 + end);
				else nxt[j] = min(nxt[j],cur[k] + mx - val + mx - end);
			}
			cur = nxt;
		}
		int ans = INF;
		rep(i, 0, p - 1) ans = min(ans, cur[i]);
		cout << "Case #" << tt << ": " << ans << "\n";
	}
	return 0;
}

