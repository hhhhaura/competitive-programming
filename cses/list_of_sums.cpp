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
	int tot = n * (n - 1) / 2;
	vector<int> b(tot + 1, 0), a;
	rep(i, 1, tot) cin >> b[i];
	sort(all(b));
	auto solve = [&](int x) {
		a.assign(n + 1, 0);
		a[1] = b[1] - x;
		a[2] = x;
		multiset<int> s;
		rep(i, 2, tot) s.insert(b[i]);
		rep(i, 3, n) {
			auto it = s.begin();
			a[i] = *it - a[1];
			s.erase(it);
			rep(j, 2, i - 1) {
				if(s.find(a[j] + a[i]) == s.end()) return 0;
				s.erase(s.find(a[j] + a[i]));
			}
		}
		rep(i, 1, n) if(a[i] < a[i - 1]) return 0;
		return 1;
	};
	rep(i, 3, n + 1) {
		int val = b[i] - b[2] + b[1];
		if(val & 1) continue;
		if(solve(val / 2)) {
			rep(j, 1, n) cout << a[j] << " \n"[j == n];
			break;
		}
	}
	return 0;
}


