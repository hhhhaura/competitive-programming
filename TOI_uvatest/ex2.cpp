#include <bits/stdc++.h>
using namespace std;
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
void add(pii p, set<pii> &s) {
	s.insert(p);
	auto it = s.lower_bound(p);
	if(it != s.begin() && next(it) != s.end()) {
		auto L = prev(it), R = next(it);
		if(!check(*L, p, *R)) {
			s.erase(s.find(p));
			return;
		}
	}
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
int main() {
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	down.insert({x1, y1});
	down.insert({x2, y2});
	up.insert({-x1, -y1});
	up.insert({-x2, -y2});
	int x, y;
	while(cin >> x >> y) {
		add({x, y}, down);
		add({-x, -y}, up);
		cout << "current down hull\n";
		for(auto i : down) cout << "(" << i.x << ", " << i.y <<") ";
		cout << "\n";
		cout << "current upper hull\n";
		for(auto i : up) cout << "(" << -i.x << ", " << -i.y << ") ";
		cout << "\n\n";
	}
}

