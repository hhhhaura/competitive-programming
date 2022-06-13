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
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, k;
		cin >> n >> k;
		int mid = (1 + n) / 2;
		vector<int> v(n + 1, 0);
		rep(i, 1, mid - 1) {
			int len = (n - (i - 1) * 2);
			v[i] = v[i - 1] + (len - 1) * 4;
		}
		auto get_num = [&](int x, int y) {
			int lay1 = (x < mid ? x - 1 : n - x);
			int lay2 = (y < mid ? y - 1 : n - y);
			int lay = min(lay1, lay2), len = n - lay * 2;
			int ans = v[lay];
			if(x == lay + 1) ans += y - lay;
			else if(y == n - lay) ans += (len - 1) + x - lay;
			else if(x == n - lay) ans += (len - 1) * 2 + n - lay - y + 1;
			else ans += (len - 1) * 3 + n - lay - x + 1;
			return ans;
		};
		auto dis = [&](int x, int y) {
			return abs(x - mid) + abs(y - mid);
		};
		int cur = 2 * (mid - 1);
		cout << "Case #" << tt << ": ";
		if(k < cur || (k & 1) != (cur & 1)) cout << "IMPOSSIBLE\n";
		else {
			int tag = 0, x = -1, y = -1;
			while(true) {
				if(dis(tag + 2, tag + 1) + get_num(tag + 2, tag + 1) >= k) break;
				tag ++;
			}
			rep(i, tag + 1, n - tag) {
				if(dis(tag + 1, i) + get_num(tag + 1, i) == k + 1) 
					x = tag + 1, y = i;
				if(dis(n - tag, i) + get_num(n - tag, i) == k + 1)
					x = n - tag, y = i;
			}
			rep(i, tag + 1, n - tag) {
				if(dis(i, n - tag) + get_num(i, n - tag) == k + 1) 
					x = i, y = n - tag;
				if(dis(i, tag + 1) + get_num(i, tag + 1) == k + 1)
					x = i, y = tag + 1;
			}
			int tpx = x, tpy = y;
			vector<int> ans = {get_num(x, y)}, ans1 = {get_num(x, y)};
			while(y > mid) y --, ans.push_back(get_num(x, y));
			while(x > mid) x --, ans.push_back(get_num(x, y));
			while(y < mid) y ++, ans.push_back(get_num(x, y));
			while(x < mid) x ++, ans.push_back(get_num(x, y));
			
			x = tpx, y = tpy;
			while(y < mid) y ++, ans1.push_back(get_num(x, y));
			while(x < mid) x ++, ans1.push_back(get_num(x, y));
			while(y > mid) y --, ans1.push_back(get_num(x, y));
			while(x > mid) x --, ans1.push_back(get_num(x, y));
			bool ok = 1;
			rep(i, 1, signed(ans1.size()) - 1)
				ok &= (ans1[i] > ans1[i - 1]);
			if(ok) ans = ans1;
			vector<pii> to;
			rep(i, 1, signed(ans.size()) - 1) {
				if(ans[i - 1] + 1 == ans[i]) continue;
				to.push_back({ans[i - 1], ans[i]});
			}
			cout << to.size() << "\n";
			rep(i, 0, signed(to.size()) - 1) 
				cout << to[i].x << " " << to[i].y << "\n";
			
			
		}

	}
	return 0;
}

