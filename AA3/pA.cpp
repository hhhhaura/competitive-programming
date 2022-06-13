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
pii exgcd(int a, int b) {
	if(b == 0) return {(a > 0 ? 1 : -1), 0};
	else {
		pii p = exgcd(b, a % b);
		return {p.second, p.first - a / b * p.second};
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	int a = 1, r = 0;
	rep(i, 1, n) {
		int a1, r1; 
		cin >> a1 >> r1;
		r1 = (a1 - r1);
		int gcd = __gcd(a1, a);
		if((r - r1) % gcd) {
			rrep(j, 1, a1) if((r - j) % gcd == 0) {
				r1 = j;
				break;
			}
		}
		cout << a1 << " " << a1 - r1 << "\n";
		pii p = exgcd(a1, -a);
		int v = (r - r1) / gcd;
		p.first *= v, p.second *= v;
		a = a / gcd * a1;
		r = ((p.first % a * a1 % a + r1) % a + a) % a;
	}
	return 0;
}


