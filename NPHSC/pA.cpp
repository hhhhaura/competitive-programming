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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<pii> a, b;
	rep(i, 0, n - 1) {
		int x, y;
		cin >> x >> y;
		a.push_back({x, y});
	}
	auto cal = [&]() {
		sort(all(b));
		int ans = 0, cur = INF, cnt = 0;
		for(auto i : b) {
			if(cur != i.first) {
				ans += max(0ll, cnt - 1);
				cnt = 1, cur = i.first;
			}
			else cnt ++;
		}
		ans += max(0ll, cnt - 1);
		return ans;
	};
	int tot = 0;
	b = a;
	tot += cal();
	b.clear();
	for(auto i : a) b.push_back({i.second, i.first});
	tot += cal();
	b.clear();
	for(auto i : a) b.push_back({i.first + i.second, i.second});
	tot += cal();
	b.clear();
	for(auto i : a) b.push_back({i.second - i.first, i.first});
	tot += cal();
	cout << tot << "\n";
	return 0;
}

