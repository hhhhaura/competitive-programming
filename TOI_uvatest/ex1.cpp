#include <bits/stdc++.h>
using namespace std;
#define lld long double
#define x first
#define y second
#define INF 1000000000000000000
#define pii pair<int, int> 
pii operator+(pii a, pii b) { return {a.x + b.x, a.y + b.y}; }
pii operator-(pii a, pii b) { return {a.x - b.x, a.y - b.y}; }
int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
int dot(pii a, pii b) { return a.x * b.x + a.y * b.y; }
int len2(pii a) { return dot(a, a); }
lld dis2seg(pii a, pii b, pii o) {
	pii v = o - a, v1 = b - a;
	lld r = dot(v, v1) / len2(v1);
	if(r < 0) return len2(o - a);
	else if(r > 1) return len2(o - b);
	else return (len2(v) - r * r * len2(v1));
}
vector<pii> v;
int main() {
	int n; cin >> n;
	v.assign(n, {0, 0});
	for(int i = 0; i < n; i ++) {
		cin >> v[i].x >> v[i].y;
	}
	lld ans = INF;
	int x, y; cin >> x >> y;
	for(int i = 0; i < n; i ++) {
		int j = (i + 1) % n;
		ans = min(ans, dis2seg(v[i], v[j], {x, y}));
	}
	cout << fixed << setprecision(9);
	cout << sqrt(ans) << "\n";
}
