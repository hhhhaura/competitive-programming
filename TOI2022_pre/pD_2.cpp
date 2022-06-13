#include "lib2249.h"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000
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

string solve(int n1, int n2) {
	int n = n1 + n2, val = n2 - 11;
	int L = ((n2 & 1) ? val / 2 + 11 : n2 / 2), R = n2 - L;
	vector<int> a(ceil(n, 2), 0), b(n / 2, 0);
	auto make = [&](vector<int> L, vector<int> R) {
		int l = 0, r = 0;
		vector<int> ans(n, 0);
		rep(i, 0, n - 1) {
			if(i & 1) ans[i] = R[r++];
			else ans[i] = L[l++];
		}
		return ans;
	};
	vector<int> fst(n, 0), sec(n, 0), cur, a1, a2;
	if(L >= ceil(n, 2)) return "-1";
	else {
		rep(i, 0, L - 1) a[i] = 2;
		rep(i, 0, R - 1) b[i] = 2;
		cur = make(a, b);
		if(cur > fst) cur.swap(fst);
		if(cur > sec) cur.swap(sec);
		if(!is_sorted(all(a))) {
			prev_permutation(all(a));
			cur = make(a, b);
			if(cur > fst) cur.swap(fst);
			if(cur > sec) cur.swap(sec);
			next_permutation(all(a));
		}
		if(!is_sorted(all(b))) {
			prev_permutation(all(b));
			cur = make(a, b);
			if(cur > fst) cur.swap(fst);
			if(cur > sec) cur.swap(sec);
		}
		vector<int> bad(n, 0);
		if(sec == bad) return "-1";
		else a1 = sec;
		sort(all(a));
		sort(all(b));
		sec.assign(n, INF);
		fst.assign(n, INF);
		bad.assign(n, INF);
		cur = make(a, b);
		if(cur < fst) cur.swap(fst);
		if(cur < sec) cur.swap(sec);
		auto cmp = [](int a, int b) {
			return a >= b;
		};
		if(!is_sorted(all(a), cmp)) {
			next_permutation(all(a));
			cur = make(a, b);
			if(cur < fst) cur.swap(fst);
			if(cur < sec) cur.swap(sec);
			prev_permutation(all(a));
		}
		if(!is_sorted(all(b), cmp)) {
			next_permutation(all(b));
			cur = make(a, b);
			if(cur < fst) cur.swap(fst);
			if(cur < sec) cur.swap(sec);
		}
		if(bad == sec) return "-1";
		else a2 = sec;
	}
	string ans = "";
	rep(i, 0, n - 1) ans += char('0' + a1[i]);
	ans += " ";
	rep(i, 0, n - 1) ans += char('0' + a2[i]);
	return ans;
}

