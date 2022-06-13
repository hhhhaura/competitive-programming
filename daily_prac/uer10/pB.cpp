#define wiwihorz
#include "distance.h"
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
#define ll long long int
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
vector<vector<double>> dis;
vector<vector<double>> v, iv;
vector<vector<int>> vis;
vector<double> b, c;
vector<int> pts;
double get_dis(int a, int b) {
	if(vis[a][b] != 0) return dis[a][b];
	else {
		double ans = query(a, b);
		dis[a][b] = dis[b][a] = ans;
		vis[a][b] = vis[b][a] = 1;
		return ans;
	}
}
void init_(int n, int k) {
	vis.assign(n, vector<int>(n, 0));
	dis.assign(n, vector<double>(n, -1));
	v.assign(k, vector<double>(k, 0));
	iv.assign(k, vector<double>(k, 0));
	b.assign(k, 0);
	c.assign(k, 0);
}
bool cmp(lld x) {
	return abs(x) < eps;
}
vector<vector<double>> solve(int n, int K, int lim) {
	int cur = 1;
	init_(n, K);
	vector<vector<double>> ans(1, vector<double>(K, 0));
	if(n == 1) return ans;
	ans.push_back(vector<double>(K, 0));
	ans[1][0] = sqrt(get_dis(0, 1));
	v[0][0] = 1.0 / ans[1][0];
	iv[0][0] = ans[1][0];
	pts.push_back(1);
	rep(i, 2, n - 1) {
		rep(j, 0, cur - 1) {
			c[j] = get_dis(pts[j], i) - get_dis(0, i) - get_dis(pts[j], 0);
			c[j] /= 2.0;
		}
		b.assign(K, 0);
		rep(j, 0, cur - 1) rep(k, 0, cur - 1)
			b[j] += v[j][k] * c[k];
		lld tot = 0;
		rep(j, 0, cur - 1) tot += b[j] * b[j];
		print(tot, get_dis(0, i));
		//vprint(all(c));
		if(get_dis(0, i) - eps > tot) {
			print(i, get_dis(0, i), tot);
			pts.push_back(i), cur ++;
			//vprint(all(pts));
			b[cur - 1] = sqrt(get_dis(0, i) - tot);
			rep(j, 0, cur - 1) iv[cur - 1][j] = b[j];
			rep(j, 0, cur - 2) {
				lld sum = 0;
				rep(k, 0, cur - 2) sum += b[k] * v[k][j];
				v[cur - 1][j] = (-sum) / b[cur - 1];
			}
			v[cur - 1][cur - 1] = 1.0 / b[cur - 1];
		}
		ans.push_back(b);
	}
	cerr << fixed << setprecision(6);
	lld tot = 0;
	rep(i, 0, K - 1) {
		lld cur = ans[1][i] - ans[2][i];
		tot += cur * cur;
	}
	print(query(2, 1), tot, cur);
	return ans;
}

