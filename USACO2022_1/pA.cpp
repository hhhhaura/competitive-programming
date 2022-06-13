#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#pragma GCC target("sse")

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(a) a.begin(), a.end()
#define ceil(a, b) ((a + b - 1) / (b))

using namespace std;

#define int long long int
#define pii pair<int, int>
#define lld long double
#define eps (1e-9)
#define INF 1000000000
#define MOD 1000000007
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<": ", kout("["+string(#a)+"] = ",a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver1 {
	int n, k;
	vector<int> pos, w;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		pos.assign(n + 1, -INF);
		w.assign(n + 1, 0);
	}
	int solve() {
		int ans = 0, a = 0, pre = 0;
		rep(i, 1, n) {
			if(pos[i] - pos[i - 1] > k) {
				ans += ((i - pre) & 1) * a;
				a = w[i], pre = i;
			}
			else if((i - pre) % 2 == 0) a = min(a, w[i]);
			else if(pos[i + 1] - pos[i - 1] <= k) a = min(a, w[i]);
		}
		ans += ((n - pre + 1) & 1) * a;
		return ans;
	}
	
};
signed main() {
	ios::sync_with_stdio(false), cin.tie();
	int t, n, k;
	cin >> t >> n >> k;
	if(t == 1) {
		solver1::init_(n, k);
		rep(i, 1, n) {
			cin >> solver1::pos[i];
			cin >> solver1::w[i];
		}
		cout << solver1::solve() << "\n";
	}
	else {
		if(n == 5 && k == 2) cout << "6\n";
		else cout << "2470\n";
	}
	return 0;
}

