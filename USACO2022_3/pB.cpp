#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define x first
#define y second
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R],++L;}
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ...e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t, k;
	cin >> t >> k, t--;
	auto pow_ = [](lld a, int times) {
		lld ans = 1;
		for(;times > 0; times >>= 1, a = a * a) {
			if(times & 1) ans = ans * a;
		}
		return ans;
	};
	lld base = pow_(0.5, t);
	rep(i, 1, t) base *= i;
	vector<lld> p(t + 1, 0), pre(t + 2, 0);
	rep(i, 0, t) {
		p[i] = base;
		rep(j, 1, i) p[i] /= j;
		rep(j, 1, t - i) p[i] /= j;
		pre[i + 1] = p[i];
		pre[i + 1] += pre[i];
		print(i, p[i], pre[i + 1]);
	}
	lld ans = 0;
	rep(i, 0, t) {
		lld prob = 1 - pow_(pre[i], k);
		lld cur = (prob * (i + t) + (1 - prob) * (0 + t - 1)) * 0.5;
		print(i, prob, cur);
		ans = max(ans, cur);
	}
	cout << fixed << setprecision(9);
	cout << ans + 1 << "\n";
	
	return 0;
}

