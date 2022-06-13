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
#define x first
#define y second
namespace solver {
	map<int, pii> mp;
	vector<int> fac, p;
	const int P = 200000;
	void init_() {
		mp.clear();
		fac.assign(P + 1, 1);
		rep(i, 2, P) {
			if(fac[i] == 1) p.push_back(i);
			for(auto j : p) {
				if(i * j > P) break;
				fac[i * j] = j;
				if(i % j == 0) break;
			}
		}
	}
	int pow_(int a, int times, int mod) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % mod) {
			if(times & 1) ans = ans * a % mod;
		}
		return ans;
	}
	void add_number(int a, int r) {
		vector<pair<int, pii>> v;
		int cur = a;
		while(fac[cur] != 1) {
			int num = fac[cur];
			v.push_back({1, {num, 0}});
			while(cur % num == 0) {
				cur /= num;
				v[v.size() - 1].x *= num;
				v[v.size() - 1].y.y ++;
			}
		}
		if(cur != 1) v.push_back({cur, {cur, 1}});
		int yes = 0, tot = 1;
		for(auto i : v) if(mp.find(i.y.x) != mp.end()) {
			tot *= i.x;
			int fac = i.y.x, cnt = i.y.y;
			pii L = {cnt, r % i.x}, R = mp[fac];
			if(L > R) swap(L, R);
			yes |= (R.y % pow_(fac, L.x, INF) != L.y);
		}
		if(!yes) {
			cout << a << " " << r << "\n";
			rep(i, 0, signed(v.size()) - 1) {
				pii p = {v[i].y.y, r % v[i].x};
				mp[v[i].y.x] = max(mp[v[i].y.x], p);
			} 
		}
		else {
			int ans = 0;
			for(auto i : v) if(mp.find(i.y.x) != mp.end()) {
				int cur = i.x, a = (tot / cur);
				ans += a * pow_(a, cur - 2, cur) * (mp[i.y.x].y % cur);
			}
			for(auto i : mp) {
				int val = pow_(i.x, i.y.x,INF);
				print(val, i.y.y);
			}
			print(a, ans);
			for(auto i : v) {
				int cur = i.x;
				pii p = {i.y.y, ans % cur};
				mp[i.y.x] = max(mp[i.y.x], p);
			}
			cout << a << " " << ans << "\n";
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_();
	rep(i, 1, n) {
		int a, r;
		cin >> a >> r;
		add_number(a, r);
	}
	return 0;
}


