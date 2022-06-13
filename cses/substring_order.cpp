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
vector<int> cnt, x, y, sa, h;
void suffix_array(string s) {
	int n = s.size(), m = 500;
	cnt.assign(m, 0);
	x.assign(n, 0);
	y.assign(n, 0);
	sa.assign(n, 0);
	rep(i, 0, n - 1) cnt[s[i]] ++, x[i] = s[i];
	rep(i, 1, m) cnt[i] += cnt[i - 1];
	rrep(i, 0, n - 1) sa[--cnt[s[i]]] = i;
	for(int k = 1; k < n; k <<= 1) {
		cnt.assign(m, 0);
		rep(i, 0, n - 1) cnt[x[i]] ++;
		rep(i, 1, m - 1) cnt[i] += cnt[i - 1];
		int ii = 0;
		rep(i, n - k, n - 1) y[ii++] = i;
		rep(i, 0, n - 1) if(sa[i] >= k) y[ii++] = sa[i] - k;
		rrep(i, 0, n - 1) sa[--cnt[x[y[i]]]] = y[i];
		y[sa[0]] = 0, ii = 0;
		rep(i, 1, n - 1) {
			int L = sa[i - 1], R = sa[i];
			if(x[L] == x[R] && L + k < n && R + k < n
				&& x[L + k] == x[R + k]);
			else ii++;
			y[sa[i]] = ii;
		}
		x.swap(y), m = ii + 1;
		if(ii + 1 == n) return;
	}	
}
void lcp(string s) {
	int n = s.size(), r = 0;
	h.assign(n, 0);
	rep(i, 0, n - 1) {
		if(r) r--;
		if(!x[i]) continue;
		int L = i, R = sa[x[i] - 1];
		while(L + r < n && R + r < n && 
			s[L + r] == s[R + r]) r ++;
		h[x[i]] = r;
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s; cin >> s;
	suffix_array(s);
	lcp(s);
	int id = 1, k;
	int n = s.size(), ans = 0;
	cin >> k;
	rep(i, 0, n - 1) {
		int v = n - sa[i] - h[i];
		if(ans + v < k) ans += v;
		else {
			cout << s.substr(sa[i], h[i] + k - ans) << "\n";
			return 0;
		}
	}
	
	return 0;
}



