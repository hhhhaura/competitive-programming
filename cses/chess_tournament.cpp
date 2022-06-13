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
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<int> a(n + 1, 0);
	set<pii> s;
	vector<pii> ans;
	int sum = 0;
	rep(i, 1, n) {
		cin >> a[i], sum += a[i];
		if(a[i]) s.insert({a[i], i});
	}
	auto fail = []() {
		cout << "IMPOSSIBLE\n";
		exit(0);
	};
	if(sum & 1) fail();
	while(s.size()) {
		auto it = prev(s.end());
		int need = it -> x, cur = it -> y;
		if(need >= s.size()) fail();
		auto R = prev(it);
		vector<pii> tmp;
		rep(i, 1, need) {
			int pos = R -> y, cnt = R -> x;
			ans.push_back({cur, pos});
			auto tp = R;
			if(R != s.begin()) R = prev(R);
			if(cnt > 1) tmp.push_back({cnt - 1, pos});
			s.erase(tp);
		}
		s.erase(it);
		for(auto i : tmp) s.insert(i);
	}
	cout << ans.size() << "\n";
	for(auto i : ans) cout << i.x << " " << i.y << "\n";
	return 0;
}


