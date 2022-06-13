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
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count)

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
	int n, m; cin >> n >> m;
	vector<vector<int>> u, d, l, r;
	vector<vector<int>> mp;
	u.assign(n + 2, vector<int>(m + 2, 0));
	d.assign(n + 2, vector<int>(m + 2, 0));
	l.assign(n + 2, vector<int>(m + 2, 0));
	r.assign(n + 2, vector<int>(m + 2, 0));
	mp.assign(n + 2, vector<int>(m + 2, 0));
	rep(i, 1, n) rep(j, 1, m) {
		cin >> mp[i][j];
	}
	vector<int> st;
	rep(j, 1, m) {
		st.clear(), st.push_back(0);
		mp[0][j] = INF;
		rep(i, 1, n) {
			while(mp[st.back()][j] <= mp[i][j]) st.pop_back();
			u[i][j] = (i - 1 - st.back());
			st.push_back(i);
		}
	}
	rep(j, 1, m) {
		st.clear(), st.push_back(n + 1);
		mp[n + 1][j] = INF;
		rrep(i, 1, n) {
			while(mp[st.back()][j] <= mp[i][j]) st.pop_back();
			d[i][j] = (st.back() - i - 1);
			st.push_back(i);
		}
	}
	rep(i, 1, n) {
		st.clear(), st.push_back(0);
		mp[i][0] = INF;
		rep(j, 1, m) {
			while(mp[i][st.back()] <= mp[i][j]) st.pop_back();
			l[i][j] = (j - 1 - st.back());
			st.push_back(j);
		}
	}
	rep(i, 1, n) {
		st.clear(), st.push_back(m + 1);
		mp[i][m + 1] = INF;
		rrep(j, 1, m) {
			while(mp[i][st.back()] <= mp[i][j]) st.pop_back();
			r[i][j] = (st.back() - j - 1);
			st.push_back(j);
		}
	}
	int ans = 0;
	rep(i, 1, n) rep(j, 1, m) {
		int U = u[i][j], D = d[i][j];
		int val = min(l[i][j], r[i][j]);
		if(U >= D) {
			int tot = ((1 + D) * D / 2) % MOD;
			ans = (ans + val * tot % MOD) % MOD;
		} 
		else {
			int tot1 = ((1 + U) * U / 2) % MOD;
			int tot2 = (D - U) * U;
			ans = (ans + val * (tot1 + tot2) % MOD) % MOD;
		}
	}
	cout << ans << "\n";
	return 0;
}

