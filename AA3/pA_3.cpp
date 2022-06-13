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
	const int P = 200000;
	vector<int> mp, fac, p;
	void init_() {
		mp.assign(P + 1, -1);
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
	pii exgcd(int a, int b) {
		if(b == 0) return {a > 0 ? 1 : -1, 0};
		else {
			pii p = exgcd(b, a % b);
			return {p.y, p.x - a / b * p.y};
		}
	}
	void add_num(int a, int r) {
		int cur = a;
		vector<pii> v;
		while(fac[cur] != 1) {
			v.push_back({fac[cur], 1});
			int num = fac[cur];
			while(cur % num == 0) {
				v[v.size() - 1].y *= num;
				cur /= num;
			}
		}
		if(cur != 1) v.push_back({cur, cur});
		int bad = 0;
		for(auto i : v) {
			int num = i.x, val = i.y, to = r % val;
			while(mp[val] == -1 && val) val /= num;
			if(val) bad |= (to % val != mp[val]);
		}
		if(bad) {
			int b = 1, k = 0;
			for(auto i : v) {
				int num = i.x, val = i.y;
				while(val && mp[val] == -1) val /= num;
				if(val) {
					int a1 = val, r1 = mp[val];
					int gcd = __gcd(a1, b);
					pii p = exgcd(a1, -b);
					p.x *= (k - r1) / gcd;
					b = a1 * b;
					k = ((a1 * p.x + r1) % b + b) % b;
				}
			}
			r = k;
		}
		for(auto i : v) {
			int num = i.x, val = i.y, to = r % val;
			while(val && mp[val] == -1) {
				mp[val] = to % val;
				val /= num;
			}
		}
		cout << a << " " << r << "\n";
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; 
	cin >> n;
	init_();
	rep(i, 1, n) {
		int a, r;
		cin >> a >> r;
		add_num(a, r);
	}
	return 0;
}


