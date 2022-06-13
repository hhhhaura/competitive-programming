#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> T(n + 1, 0);
	vector<int> S(n + 1, 0);
	vector<int> D(n + 1, 0);
	rep(i, 1, n - 1) cin >> T[i];
	rep(i, 1, n) cin >> S[i];
	rep(i, 1, n) cin >> D[i];
	auto solve = [&](int id) {
		int left = m;
		rep(i, 1, id - 1) left -= T[i];
		int L = 0, R = 1000000000;
		int best = 0, rec = 0;
		if(left < 0) return 0ll;
		while(R - L > 1) {
			int mid = (L + R) / 2;
			int t = 0, val = 0, bad = 0;
			rep(i, 1, id) if(S[i] >= mid) {
				if(D[i] == 0) {
					bad = 1;
					break;
				}
				int x = (S[i] - mid) / D[i] + 1;
				t += x, val += (S[i] + S[i] - (x - 1) * D[i]) * x / 2;
			}
			if(t > left || bad) L = mid;
			else R = mid, best = val, rec = t;
		}
		left -= rec;
		return best + left * L;
	};
	int ans = 0;
	rep(i, 1, n) ans = max(ans, solve(i));
	cout << ans << "\n";
	return 0;
}

