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
#define INF 9000000000000000000
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
	rep(tt, 1, t) {
		int n; cin >> n;
		vector<pii> a(n + 1, {0, 0}), b(n + 1, {0, 0});
		vector<vector<int>> ord(n + 1, vector<int>(n + 1, 0));
		rep(i, 1, n) cin >> a[i].x >> a[i].y;
		rep(i, 0, n) cin >> b[i].x >> b[i].y;
		vector<int> v(n, 0);
		iota(all(v), 1);
		bool yes = 0;
		cout << "Case #" << tt << ": ";
		auto dis = [](pii a, pii b) {
			pii c = {a.x - b.x, a.y - b.y};
			return c.x * c.x + c.y * c.y;
		};
		rep(i, 1, n) {
			iota(all(ord[i]), 0);
			sort(all(ord[i]), [&](int x, int y) {
				int l = dis(a[i], b[x]);
				int r = dis(a[i], b[y]);
				if(l == r) return  x > y;
				else return l < r;
			});
		}
		do {
			vector<int> vis(n + 1, 0), to(n + 1, 0);
			int good = 1;
			for(auto i : v) {
				int id = 0;
				rep(j, 0, n) {
					if(!vis[ord[i][j]]) {
						id = ord[i][j];
						break;
					}
				}
				if(id == 0) {
					good = 0;
					break;
				}
				else vis[id] = 1, to[i] = id;
			}
			if(good == 1) {
				yes = 1;
				cout << "POSSIBLE\n";
				rep(i, 0, n - 1) cout << v[i] << " " << to[v[i]] + 1 << "\n";
				break;
			}
		} while(next_permutation(all(v)));
		if(!yes) cout << "IMPOSSIBLE\n";
	}
	return 0;
}


