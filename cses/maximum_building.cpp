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
	int n, m;
	cin >> n >> m;
	vector<vector<int>> mp(n + 1, vector<int>(m + 1, 0));
	vector<vector<int>> mx(n + 1, vector<int>(m + 1, 0));
	rep(i, 1, n) rep(j, 1, m) {
		char c; cin >> c;
		mp[i][j] = c == '.';
	}
	rep(i, 1, n) rep(j, 1, m) {
		if(mp[i][j]) mx[i][j] = mx[i - 1][j] + 1;
	}
	auto solve = [&](vector<int> &v) {
		vector<int> L(m + 1, 0), R(m + 1, 0);
		vector<int> st;
		rep(i, 1, m) {
			while(st.size() && v[st.back()] >= v[i]) st.pop_back();
			if(!st.size()) L[i] = 0;
			else L[i] = st.back();
			st.push_back(i);
		}
		st.clear();
		rrep(i, 1, m) {
			while(st.size() && v[st.back()] >= v[i]) st.pop_back();
			if(!st.size()) R[i] = m + 1;
			else R[i] = st.back();
			st.push_back(i);
		} 
		int ans = 0;
		rep(i, 1, m) ans = max(ans, (R[i] - L[i] - 1) * v[i]);
		return ans;
	};	
	int ans = 0;
	rep(i, 1, n) ans = max(ans, solve(mx[i]));
	cout << ans << "\n";

	return 0;
}


