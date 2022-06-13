#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define lld long double
#define x first
#define y second
#define INF 1000000000000000000
#define pii pair<int, int> 
#define print(a...) kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
int len2(pii a) { return dot(a, a); }
set<pii> up, down;
bool check(pii o, pii a, pii b) {
	return cross(a - o, b - o) > 0;
}
bool check_hull(pii p, set<pii> &s) {
	auto it = s.lower_bound(p);
	if(s.find(p) != s.end()) return 0;
	if(it != s.end() && it != s.begin()) {
		auto L = prev(it), R = it;
		return check(*L, p, *R);
	}
	return 1;
}
void add(pii p, set<pii> &s) {
	if(!check_hull(p, s)) return;
	s.insert(p);
	auto it = s.lower_bound(p);
	while(true) {
		if(it == s.begin() || prev(it) == s.begin()) break;
		auto a = prev(it), b = prev(a);
		if(!check(*b, *a, *it)) s.erase(a);
		else break;
	}
	while(true) {
		if(next(it) == s.end() || next(next(it)) == s.end()) break;
		auto a = next(it), b = next(a);
		if(!check(*it, *a, *b)) s.erase(a);
		else break;
	}
	return;
}
signed main() {
	int t; cin >> t;
	while(t--) {
		int tp; cin >> tp;
		int x, y; cin >> x >> y;
		if(tp == 1) {
			add({x, y}, down);
			add({-x, -y}, up);
		}
		else {
			bool yes = !check_hull({x, y}, down) &&
				!check_hull({-x, -y}, up);
			if(yes) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}


