#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()

using namespace std;

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr << "Line " << __LINE__, kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
#define m first
#define k second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 1, 0), pre(n + 1, INF), cur(n + 1, INF);
	vector<pii> v(n + 1, {0, 0});
	auto val = [&](pii p, int x) {
		return p.m * x + p.k;
	};
	auto check = [&](pii a, pii b, pii c) {
		return (c.k - a.k) * (a.m - b.m) <=
			(b.k - a.k) * (a.m - c.m);
	}; 
	cur[0] = 0;
	rep(i, 1, n) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	rep(i, 1, k) {
		pre = cur;
		cur.assign(n + 1, INF);
		int l = 0, r = 0;
		v[0] = {-2ll * a[i - 1], pre[i - 1] + a[i - 1] * a[i - 1]};
		rep(j, i, n) {
			while(l < r && val(v[l], a[j]) >= val(v[l + 1], a[j])) l++;
			cur[j] = val(v[l], a[j]) + a[j] * a[j];
			pii p = {-2ll * a[j], pre[j] + a[j] * a[j]};
			while(l < r && check(v[r - 1], v[r], p)) r--;
			v[++r] = p;
		}
	}
	cout << cur[n] << "\n";


	
	return 0;
}


