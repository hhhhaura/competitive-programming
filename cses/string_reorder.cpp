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
	string s; cin >> s;
	int n = s.size();
	vector<int> cnt(26, 0);
	int mx = 0, id = 0;
	for(auto i : s) {
		int cur = i - 'A';
		cnt[cur] ++;
		if(cnt[cur] > mx) {
			mx = cnt[cur];
			id = cur;
		}
	}
	if(mx <= ceil(n, 2)) {
		string ans = "";
		int pre = -1;
		rep(i, 1, n) {
			int len = n - i + 1, cur = -1;
			rrep(j, 0, 25) if(j != pre) {
				if(cnt[j] * 2 - 1 == len) {
					cur = j;
					break;
				}
				else if(cnt[j]) cur = j;
			}
			assert(cur != -1);
			ans += char(cur + 'A');
			cnt[cur] --;
			pre = cur;
		}
		cout << ans << "\n";
	}
	else cout << "-1\n";
	return 0;
}


