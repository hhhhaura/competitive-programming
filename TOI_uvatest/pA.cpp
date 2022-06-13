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
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	vector<pii> v;
	vector<int> a(10, 0);
	iota(all(a), 0);
	do {
		pii cur = {0, 0};
		rep(i, 0, 4) cur.x = (cur.x * 10 + a[i]);
		rep(i, 5, 9) cur.y = (cur.y * 10 + a[i]);
		v.push_back(cur);
	} while(next_permutation(all(a)));
	sort(all(v));
	auto output = [&](pii a, int n) {
		// 79546 / 01283 = 62
		cout << a.x << " / ";
		if(a.y < 10000) cout << "0";
		cout << a.y << " = " << n << "\n";
	};
	int n; cin >> n;
	while(true) {
		int yes = 0;
		for(auto i : v) {
			if(i.x == i.y * n) {
				output(i, n);
				yes = 1;
			}
		}
		if(!yes) cout << "There are no solutions for " << n << ".\n";
		cin >> n;
		if(!n) break;
		cout << "\n";
	}
	
	return 0;
}

