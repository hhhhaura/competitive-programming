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
vector<int> fail_function(string s) {
	int n = s.size();
	vector<int> v(n + 1, -1);
	rep(i, 1, n - 1) {
		int cur = v[i - 1];
		while(cur != -1 && s[cur + 1] != s[i]) cur = v[cur];
		if(s[cur + 1] == s[i]) cur ++;
		v[i] = cur;
	}
	return v;
}
int KMP(string a, string b) {
	int n = a.size(), m = b.size();
	int cnt = 0, j = -1;
	vector<int> v = fail_function(b);
	rep(i, 0, n - 1) {
		while(j != -1 && b[j + 1] != a[i]) j = v[j];
		if(b[j + 1] == a[i]) j ++;
		if(j == m - 1) cnt ++;
	}
	return cnt;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string a, b;
	cin >> a >> b;
	cout << KMP(a, b) << "\n";
	return 0;
}


