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
namespace seg {
	int n;
	const int P = 2000000;
	vector<int> tag, v;
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int l = get(L, mid), r = get(mid + 1, R);
		v[nd] = ((tag[l] ? (mid - L + 1) : v[l]) + (tag[r] ? (R - mid) : v[r]));
	}
	void init_() {
		tag.assign(2 * P + 1, 0);
		v.assign(2 * P + 1, 0);
	}
	void modify(int L, int R, int l, int r, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) tag[nd] += val;
		else {
			modify(L, mid, l, r, val);
			modify(mid + 1, R, l, r, val);
			pull(L, R);
		}
	}
	int get_val() {
		return tag[get(0, P)] ? P + 1 : v[get(0, P)];
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<pair<pii, pii>> v;
	seg::init_();
	int ans = 0, cur = 0, P = 2000000, p = 1000000;
	rep(i, 1, n) {
		int l, r, u, d;
		cin >> l >> u >> r >> d;
		v.push_back({{l, 1}, {u + p, d + p}});
		v.push_back({{r, -1}, {u + p, d + p}});
	}
	sort(all(v));
	for(auto i : v) {
		int piv = i.first.first, tp = i.first.second;
		int L = i.second.first + 1, R = i.second.second;
		ans += seg::get_val() * (piv - cur);
		cur = piv;
		seg::modify(0, P, L, R, tp);
	}
	cout << ans << "\n";
	return 0;
}



