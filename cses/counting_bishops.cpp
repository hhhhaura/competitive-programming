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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	if(n == 1) {
		cout << "1\n";
		return 0;
	}
	if(k > 2 * n - 1) {
		cout << "0\n";
		return 0;
	}
	vector<int> l, r;
	for(int i = 1; i < n; i += 2) {
		l.push_back(i);
		l.push_back(i);
	}
	for(int i = 2; i < n; i += 2) {
		r.push_back(i);
		r.push_back(i);
	}
	if(n & 1) l.push_back(n);
	else r.push_back(n);
	int ll = l.size(), rr = r.size();
	vector<vector<int>> L(ll + 1, vector<int>(ll + 1, 0));
	vector<vector<int>> R(rr + 1, vector<int>(rr + 1, 0));
	auto solve = [&](int n, vector<vector<int>> &v, vector<int> &a) {
		v[0][0] = 1;
		rep(i, 1, n) rep(j, 0, a[i - 1]) {
			v[i][j] += v[i - 1][j];
			if(j) v[i][j] += v[i - 1][j - 1] * (a[i - 1] - j + 1) % MOD;
			v[i][j] %= MOD;
		}
	};
	solve(ll, L, l);
	solve(rr, R, r);
	int ans = 0;
	rep(i, 0, k) {
		if(i > ll || k - i > rr) continue;
		ans += L[ll][i] * R[rr][k - i] % MOD;
		ans %= MOD;
	}
	cout << ans << "\n";

	return 0;
}


