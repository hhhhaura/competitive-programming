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
namespace DSU {
	int n;
	vector<int> par, rk;
	void init_(int _n) {
		n = _n;
		par.assign(n + 1, 0);
		iota(all(par), 0);
		rk.assign(n + 1, 0);
	}
	int find_par(int a) {
		if(par[par[a]] == a) return par[a];
		else return par[a] = find_par(par[a]);
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa]++;
	}
};
using namespace DSU;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	const int P = 1000000;
	vector<pii> a(n, {0, 0});
	vector<pair<int, pii>> es;
	rep(i, 0, n - 1) cin >> a[i].x >> a[i].y;
	sort(all(a));
	auto dis=[&](pii a, pii b) {
		pii c = {a.x - b.x, a.y - b.y};
		return c.x * c.x + c.y * c.y;
	};
	rep(i, 0, n - 1) {
		int L = -1, R = -1;
		int x = a[i].x, y = a[i].y;
		rep(j, max(0ll, i - 100), i - 1) {
			if(L == -1) L = j;
			else if(dis(a[j], a[i]) < dis(a[L], a[i])) L = j;
		}
		rep(j, i + 1, min(i + 100, n - 1)) {
			if(R == -1) R = j;
			else if(dis(a[j], a[i]) < dis(a[R], a[i])) R = j;
		}
		if(L != -1) es.push_back({dis(a[L], a[i]),{L, i}});
		if(R != -1) es.push_back({dis(a[R], a[i]),{R, i}});
	}
	init_(n);
	sort(all(es));
	int ans = 0;
	for(auto i : es) if(!same(i.y.x, i.y.y)) {
		ans += i.x;
		unite(i.y.x, i.y.y);
	}
	cout << ans << "\n";

	return 0;
}



