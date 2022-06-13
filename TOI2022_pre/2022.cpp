#define wiwihorz
#include <bits/stdc++.h>
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
#define print(a...) cerr<<"LINE"<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R){while(L < R)cerr<<*L<<" \n"[next(L)==R], ++L;}
void kout() {cerr << endl;}
template<class T1, class ...T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int a, b; cin >> a >> b;
	if(b & 1) {
		if(b < 11 || a <= 9) cout << "-1\n";
		else if(b == 11 && a <= 11) cout << "-1\n";
		else if(b == 11) {	
			vector<int> L, R;
			int val = (b - 11) / 2, n = a + b;
			rep(i, 1, 11) L.push_back(2);
			while(L.size() < ceil(n, 2)) L.push_back(0);
			while(R.size() < n / 2) R.push_back(0);
			if(L.back() == 0) {
				rep(i, 0, signed(L.size()) - 2) {
					if(L[i] == 2 && L[i + 1] == 0) {
						swap(L[i], L[i + 1]);
						break;
					}
				}
			}
			int l = 0, r = 0;
			rep(i, 1, (a + b)) {
				if(i & 1) cout << L[l++];
				else cout << R[r++];
			}
			cout << "\n";
			reverse(all(L));
			l = 0, r = 0;
			rep(i, 1, (a + b)) {
				if(i & 1) cout << L[l++];
				else cout << R[r++];
			}
			cout << "\n";
		}
		else {
			vector<int> L, R;
			int val = (b - 11) / 2, n = a + b;
			rep(i, 1, val + 11) L.push_back(2);
			while(L.size() < ceil(n, 2)) L.push_back(0);
			rep(i, 1, val) R.push_back(2);
			while(R.size() < n / 2) R.push_back(0);
			assert(R.size() > 1);

			if(L.back() == 0) swap(R[R.size() - 1], L[L.size() - 1]);
				rep(i, 0, signed(R.size()) - 2) {
					if(R[i] == 2 && R[i + 1] == 0) {
						swap(R[i], R[i + 1]);
						break;
					}
				}
			int l = 0, r = 0;
			rep(i, 1, (a + b)) {
				if(i & 1) cout << L[l++];
				else cout << R[r++];
			}
			cout << "\n";
			L.clear(), R.clear();
			rep(i, 1, val + 11) L.push_back(2);
			while(L.size() < ceil(n, 2)) L.push_back(0);
			rep(i, 1, val) R.push_back(2);
			while(R.size() < n / 2) R.push_back(0);
			int yes = 0;
			rep(i, 0, signed(R.size()) - 2) {
				if(R[i] == 2 && R[i + 1] == 0) {
					swap(R[i], R[i + 1]);
					yes = 1;
					break;
				}
				
			}
			assert(yes);
			reverse(all(L));
			reverse(all(R));
			l = 0, r = 0;
			rep(i, 1, (a + b)) {
				if(i & 1) cout << L[l++];
				else cout << R[r++];
			}
			cout << "\n";
		}
	}
	else  {
		if(a == 1 && b == 2) cout << "022\n220\n";
		else if(a == 1) {
			rep(i, 1, b - 2) cout << "2";
			cout << "022";
			cout << "\n";
			
			cout << "220";
			rep(i, 1, b - 2) cout << "2";
			cout << "\n";
		}
		else {
			rep(i, 1, b - 1) cout << "2";
			cout << "002";
			rep(i, 1, a - 2) cout << "0";
			cout << "\n";

			rep(i, 1, a - 1) cout << "0";
			cout << "220";
			rep(i, 1, b - 2) cout << "2";
			cout << "\n";
			
		}
	}
	return 0;
}



