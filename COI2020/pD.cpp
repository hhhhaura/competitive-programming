#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("["+string(#a)+"] = ", a)
void vprint(auto L,auto R){while(L<R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout(){cerr<< endl;}
template<class T1,class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ",kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1, 0), v(n + 1, 0);
	auto query = [&](int L, int R) {
		cout << "? " << L << " " << R << "\n";
		cout.flush();
		int x; cin >> x;
		return x;
	};
	auto report = [&]() {
		cout << "! ";
		rep(i, 1, n) cout << (a[i] ? ")" : "(");
		cout << "\n";
		cout.flush();
	};
	a[n] = 1;
	map<int, int> pos;
	pos[0] = 0, pos[1] = 1;
	v[1] = 1;
	rep(i, 2, n - 1) {
		int pre = v[i - 1], x = 0;
		if(pos.find(pre - 1) != pos.end()) 
			x = query(pos[pre - 1] + 1, i);
		a[i] = x;
		v[i] = pre + (a[i] ? -1 : 1);
		pos[v[i]] = i;
	}
	report();
	return 0;
}


