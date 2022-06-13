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
	string ss; cin >> ss;
	int m; cin >> m;
	int n = ss.size();
	vector<int> a(n + 1, 0);
	multiset<int> s[2], cnt[2];
	rep(i, 0, 1) {
		s[i].insert(0);
		s[i].insert(n + 1);
	}
	rep(i, 1, n) {
		a[i] = ss[i - 1] - '0';
		s[a[i]].insert(i);
	}
	rep(i, 0, 1) {
		for(auto j = s[i].begin(); next(j) 
			!= s[i].end(); j = next(j)) {
			cnt[i].insert(*next(j) - *j);
		}
	}
	auto insert = [&](int x, multiset<int> &s, multiset<int> &cnt) {
		auto it = s.lower_bound(x);
		int L = *prev(it), R = *it;
		cnt.erase(cnt.find(R - L));
		cnt.insert(R - x);
		cnt.insert(x - L);
		s.insert(x);
	};
	auto erase = [&](int x, multiset<int> &s, multiset<int> &cnt) {
		auto it = s.lower_bound(x);
		int L = *prev(it), R = *next(it);
		cnt.erase(cnt.find(x - L));
		cnt.erase(cnt.find(R - x));
		cnt.insert(R - L);
		s.erase(s.find(x));
	};
	rep(i, 1, m) {
		int x; cin >> x;
		erase(x, s[a[x]], cnt[a[x]]);
		a[x] ^= 1;
		insert(x, s[a[x]], cnt[a[x]]);
		cout << max(*prev(cnt[0].end()), 
			*prev(cnt[1].end())) - 1 << " \n"[i == m];
	}
	return 0;
}


