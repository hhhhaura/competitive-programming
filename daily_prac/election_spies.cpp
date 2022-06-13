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
	int n; cin >> n;
	auto query = [&](vector<int> a) {
		if(a.size() == 0) return 0ll;
		cout << "Q " << a.size();
		for(auto i : a) cout << " " << i;
		cout << endl;
		int x; cin >> x;
		return x;
	};
	int ii = 0, yes = 0;
	const int P = 15;
	vector<int> L, R;
	rrep(i, 0, 15) {
		L.clear();
		R.clear();
		rep(j, 1, n) {
			if((j >> i) & 1) L.push_back(j);
			else R.push_back(j);
		}
		int x = query(L), y = query(R);
		if((x == L.size() || !x) 
			&& (y == R.size() || !y)) {
			ii = i;
			yes = (L.size() == x);
			break;
		}
	}
	int A, B;
	if(!yes) L.swap(R);
	int l = -1, r = L.size() - 1;
	while(r - l > 1) {
		int mid = (l + r) / 2;
		vector<int> v = R;
		rep(i, 0, mid) v.push_back(L[i]);
		int x = query(v);
		if(!x) l = mid;
		else r = mid;
	}
	A = L[r];
	l = -1, r = R.size() - 1;
	while(r - l > 1) {
		int mid = (l + r) / 2;
		vector<int> v = L;
		rep(i, 0, mid) v.push_back(R[i]);
		int x = query(v);
		if(x == v.size()) l = mid;
		else r = mid;
	}
	B = R[r];
	cout << "A " << A << " " << B << endl; 
	return 0;
}

