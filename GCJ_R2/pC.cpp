#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
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
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	const int P = 100000;
	vector<int> a(P + 1, 0);
	vector<int> b(P + 1, 0);
	rep(i, 1, P) rep(j, 1, i - 1) {
		lld val = sqrt(i * i + j * j);
		a[int(val + 1)] += 2;
	}
	rep(i, 1, n) {
		lld val = sqrt(i * i * 2ll);
		a[int(val + 1)] += 1;
	}
	vector<int> pre(P + 1, 0), cur(P + 1, 0);
	rep(i, 1, P) {
		cur.assign(P + 1, 0);
		rep(j, 1, i - 1) {
			lld val = sqrt(i * i - j * j);
			
		}
	}
	return 0;
}

