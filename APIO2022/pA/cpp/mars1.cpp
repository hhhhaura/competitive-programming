#define wiwihorz
#include "mars.h"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define ll long long int
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
string process(vector<vector<string>> a, int i, int j, int k, int n) {
	int mid = (n - 1 -  k) * 2;
	int len = (2 * n + 1 - mid - 2), cur = len + 2;
	if(mid == i && mid == j) {
		string ans(200, '0');
		ans[0] = a[0][0][0];
		ans[1] = a[0][1][0];
		rep(i, 0, len - 1) ans[2 + i] = a[0][2][i];
		ans[cur] = a[1][0][0];
		ans[cur + 1] = a[1][1][0];
		rep(i, 0, len - 1) ans[cur + 2 + i] = a[1][2][i];
		rep(i, 0, len - 1) {
			ans[(2 + i) * cur] = a[2][0][i];
			ans[(2 + i) * cur + 1] = a[2][1][i];
			rep(j, 0, len - 1) {
				int val = a[2][2][i * len + j];
				ans[(2 + i) * cur + 2 + j] = val;
			}
		}
		a[0][0] = ans;
	}
	else if(mid == i) {
		string to = a[2][0];
		a[0][0][1] = a[1][0][0];
		rep(i, 0, len - 1) a[0][0][i + 2] = to[i];
	}
	else if(mid == j) {
		string to = a[0][2];
		a[0][0][1] = a[0][1][0];
		rep(i, 0, len - 1) a[0][0][i + 2] = to[i];
	}

	if(mid == 0) {
		int tot = 2 * n + 1, cnt = 0;
		vector<int> vis(tot * tot, 0);
		string mp = a[0][0];
		auto val = [&](int x, int y) {
			return x * tot + y;
		};
//		rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
//			int to = val(i, j);
//			cerr << mp[to] << " \n"[j + 1 == tot];
//		}
		queue<int> q;
		vector<int> dirx = {0, 0, 1, -1};
		vector<int> diry = {1, -1, 0, 0};
		rep(i, 0, tot - 1) rep(j, 0, tot - 1) {
			if(mp[val(i, j)] == '0'|| vis[val(i, j)]) continue;
			cnt ++, vis[val(i, j)] = 1;
			q.push(val(i, j));
			while(q.size()) {
				int cur = q.front(); q.pop();
				int x = cur / tot, y = cur % tot;
				rep(tp, 0, 3) {
					int nx = dirx[tp] + x;
					int ny = diry[tp] + y;
					if(nx < 0 || ny < 0 || nx >= tot || ny >= tot) continue;
					if(vis[val(nx, ny)] || mp[val(nx, ny)] == '0') continue;
					vis[val(nx, ny)] = 1;
					q.push(val(nx, ny));
				}
			}
		}
		string ans(100, '0');
		rep(i, 0, 20) if((cnt >> i) & 1) ans[i] = '1';
		a[0][0] = ans;
	}
	a[0][0].resize(100);
	return a[0][0];
}

