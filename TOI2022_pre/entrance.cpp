#define wiwihorz
#include <bits/stdc++.h>
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
#define print(a...) cerr<<"LINE"<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() {cerr << endl;}
template<class T1, class ...T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, r;
	cin >> n >> r;
	map<pii, int> cnt;
	while(n --) {
		int x, y;
		cin >> x >> y;
		rep(i, -10, 10) rep(j, -10, 10) {
			int nx = x + i, ny = y + j;
			pii p = {nx - x, ny - y};
			if(p.x * p.x + p.y * p.y > r * r) continue;
			cnt[pii(nx, ny)] ++;
		}
	}
	int ans = 0;
	for(auto i : cnt) if(i.y & 1) ans ++;
	cout << ans << "\n";
	return 0;
}


