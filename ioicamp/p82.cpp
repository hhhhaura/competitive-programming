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
#define x first
#define y second
int n, m;
bool try1(pii a, pii b, pii c, pii d) {
	if(a.x != c.x || a.y + 1 != c.y) return 0;
	if(a.x + 1 != d.x || a.y != d.y) return 0;
	if(b.x != d.x || b.y - 1 != d.y) return 0;
	if(b.x - 1 != c.x || b.y != c.y) return 0;
	if(a.x + 1 != b.x || a.y + 1 != b.y) return 0;
	return 1;
}
bool try2(pii a, pii b, pii c) {
	if((a.x == 1 || a.x == n) && (a.y == 1 || a.y == m)) {
		if(abs(a.x - c.x) + abs(a.y - c.y) > 1) return 0;
		if(abs(a.x - b.x) + abs(a.y - b.y) > 1) return 0;
		return 1;
	}
	return 0;
}
bool onedge(pii a) {
	return a.x == n || a.x == 1 || a.y == m || a.y == 1;
}
bool check1(pii a, pii b, pii c, pii d) {
	vector<pair<pii, int>> v;
	v.push_back({a, 0});
	v.push_back({b, 0});
	v.push_back({c, 1});
	v.push_back({d, 1});
	sort(all(v));
	int cur = -1;
	for(auto i : v) if(i.first.x == 1) {
		if(i.first.y == m) continue;
		if(cur == -1) cur = i.second;
		else if(cur == i.second) return 0 ;
		else cur = i.second;
	}
	for(auto i : v) if(i.first.y == m) {
		if(i.first.x == n) continue;
		if(cur == -1) cur = i.second;
		else if(cur == i.second) return 0 ;
		else cur = i.second;
	}
	reverse(all(v));
	for(auto i : v) if(i.first.x == n) {
		if(i.first.y == 1) continue;
		if(cur == -1) cur = i.second;
		else if(cur == i.second) return 0;
		else cur = i.second;
	}
	for(auto i : v) if(i.first.y == 1) {
		if(i.first.x == 1) continue;
		if(cur == -1) cur = i.second;
		else if(cur == i.second) return 0;
		else cur = i.second;
	}
	return 1;
}
bool check2(pii a, pii b, pii c, pii d) {
	vector<pii> v;
	v.push_back({(n == 1 ? a.y : a.x), 0});
	v.push_back({(n == 1 ? b.y : b.x), 0});
	v.push_back({(n == 1 ? c.y : c.x), 1});
	v.push_back({(n == 1 ? d.y : d.x), 1});
	sort(all(v));
	return (v[0].second != v[1].second);
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		pii a, b, c, d;
		cin >> a.x >> a.y >> b.x >> b.y;
		cin >> c.x >> c.y >> d.x >> d.y;
		if(a > b) swap(a, b);
		if(c > d) swap(c, d);
		if(try1(a, b, c, d) || try1(c, d, a, b)) cout << "No\n";
		else if(try2(a, c, d) || try2(b, c, d) || 
			try2(c, a, b) || try2(d, a, b)) cout << "No\n";
		else if(onedge(a) && onedge(b) && onedge(c) 
			&& onedge(d) && check1(a, b, c, d)) cout << "No\n";
		else if((n == 1 || m == 1) && check2(a, b, c, d)) cout << "No\n";
		else cout << "Yes\n";
	}
	return 0;
}

