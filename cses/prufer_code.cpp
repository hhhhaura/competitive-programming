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
	int n; cin >> n;
	vector<int> a(n - 1, 0), lst(n + 1, 0);
	set<int> s;
	rep(i, 1, n - 2) {
		cin >> a[i];
		s.insert(a[i]);
		lst[a[i]] = max(lst[a[i]], i);
	}
	priority_queue<int, vector<int>, greater<int>> q;
	vector<pii> ans;
	rep(i, 1, n) if(s.find(i) == s.end()) q.push(i);
	rep(i, 1, n - 2) {
		int cur = q.top(); q.pop();
		ans.push_back({cur, a[i]});
		if(i == lst[a[i]]) q.push(a[i]);
	}	
	int L = q.top(); q.pop();
	int R = q.top(); q.pop();
	ans.push_back({L, R});
	for(auto i : ans) cout << i.first << " " << i.second << "\n";
	return 0;
}


