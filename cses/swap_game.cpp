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

#define INF 1000000000
#define MOD 1000000007
#define eps (1e-9)
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
	const int P = 387420489;
	vector<bool> vis(P, 0);
	auto to_vec = [](int num) {
		vector<int> v;
		rep(i, 0, 8) {
			v.push_back(num % 9);
			num /= 9;
		}
		return v;
	};
	auto to_num = [](vector<int> v) {
		int ans = 0;
		rrep(i, 0, 8) {
			ans *= 9;
			ans += v[i];
		}
		return ans;
	};
	vector<int> v(9, 0);
	rep(i, 0, 8) cin >> v[i], v[i]--;
	int num = to_num(v);
	int ed = to_num({0, 1, 2, 3, 4, 5, 6, 7, 8});
	vis[num] = 1;
	queue<int> q, st;
	q.push(num);
	st.push(0);
	while(q.size()) {
		int cur = q.front(); q.pop();
		int step = st.front(); st.pop();
		if(cur == ed) {
			cout << step << "\n";
			return 0;
		}
		vector<int> v = to_vec(cur);
		rep(i, 0, 2) rep(j, 0, 2) {
			int a = (i + 1) * 3 + j;
			int b = i * 3 + (j + 1);
			int c = i * 3 + j;
			if(i + 1 < 3) {
				swap(v[a], v[c]);
				int to = to_num(v);
				if(vis[to] == 0) {
					vis[to] = 1;
					q.push(to);
					st.push(step + 1);
				}
				swap(v[a], v[c]);
			}
			if(j + 1 < 3) {
				swap(v[b], v[c]);
				int to = to_num(v);
				if(vis[to] == 0) {
					vis[to] = 1;
					q.push(to);
					st.push(step + 1);
				}
				swap(v[b], v[c]);
			}
		} 
	}
	return 0;
}


