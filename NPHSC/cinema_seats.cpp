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
	string s; cin >> s;
	int n = s.size();
	vector<int> a;
	int cnt = 0, ans = 0;
	rep(i, 0, n - 1) {
		char c = s[i]; 
		if(c == '1') a.push_back(-1);
		else if(!a.size() || a.back() == -1) {
			a.push_back(1), cnt++;
		}
		else a[a.size() - 1] ++;
	}
	rep(i, 0, signed(a.size()) - 1) {
		if(i && i + 1 < a.size() && a[i] == -1) {
			if(cnt > 2) ans = max(ans, a[i - 1] + a[i + 1] + 1);
			else ans = max(ans, a[i - 1] + a[i + 1]);
		}
		else ans = max(ans, a[i] + (cnt > 1));
	}
	cout << ans << "\n";
	return 0;
}

