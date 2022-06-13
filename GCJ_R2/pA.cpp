#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
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
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	vector<vector<int>> v(10000, vector<int>(10000, 0));
	rep(tt, 1, t) {
		int n, k;
		cin >> n >> k;
		bool yes = 0;
		int cur = n - 1;
		cout << "Case #" << tt << ": "; 
		if(k < n - 1 || (k & 1)) cout << "IMPOSSIBLE\n";
		else {
			int cnt = 0, mid = (1 + n) / 2;
			auto dis = [&](int x, int y) {
				return (abs(x - mid) + abs(y - mid));
			};
			int x, y;
			rep(i, 0, n) {
				rep(j, 1 + i, n - i) {
					if(cnt + dis(i + 1, j) == k) {
						x = i + 1, y = j;
					}
					v[i + 1][j] = ++cnt;
				}
				rep(j, 2 + i, n - i) {
					if(cnt + dis(j, n - i) == k) {
						x = j, y = n - i;
					}
					v[j][n - i] = ++cnt;
				}
				rrep(j, 1 + i, n - i - 1) {
					if(cnt + dis(n - i, j) == k) {
						x = n - i, y = j;
					}
					v[n - i][j] = ++cnt;
				}
				rrep(j, 2 + i, n - i - 1) {
					if(cnt + dis(j, i + 1) == k) {
						x = j, y = i + 1;
					}
					v[j][1 + i] = ++cnt;
				}
			}
			int tpx = x, tpy = y;
			rep(i, 1, n) vprint(all(v[i]));
			vector<int> ans = {v[x][y]}, ans1 = {v[x][y]};
			while(y > mid) y --, ans.push_back(v[x][y]);
			while(x > mid) x --, ans.push_back(v[x][y]);
			while(y < mid) y ++, ans.push_back(v[x][y]);
			while(x < mid) x ++, ans.push_back(v[x][y]);
			
			x = tpx, y = tpy;
			while(y < mid) y ++, ans1.push_back(v[x][y]);
			while(x < mid) x ++, ans1.push_back(v[x][y]);
			while(y > mid) y --, ans1.push_back(v[x][y]);
			while(x > mid) x --, ans1.push_back(v[x][y]);
			bool ok = 1;
			rep(i, 1, signed(ans1.size()) - 1)
				ok &= (ans1[i] > ans1[i - 1]);
			if(ok) ans = ans1;
			print(ans1.size());
			vprint(all(ans));
			vector<pii> to;
			rep(i, 1, signed(ans.size()) - 1) {
				if(ans[i - 1] + 1 == ans[i]) continue;
				to.push_back({ans[i - 1], ans[i]});
			}
			cout << to.size() << "\n";
			rep(i, 0, signed(to.size()) - 1) 
				cout << to[i].x << " " << to[i].y << "\n";
		}
	}
	return 0;
}

