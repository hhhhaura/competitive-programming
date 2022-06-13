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
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count)

#ifdef wiwihorz
#define print(a...) cerr << "Line " << __LINE__, kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, q;
	vector<int> a, ans, mx, val, to;
	vector<pii> v;
	void init_(int _n, int _q) {
		n = _n, q = _q;
		a.assign(n + 1, 0);
		ans.assign(q + 1, 0);
		v.assign(q + 1, {0, 0});
		mx.assign(n + 1, 0);
		val.assign(n + 1, 0);
		to.assign(n + 1, 0);
		a[0] = INF;
	}
	void solve(int L, int R, vector<int> qs) {
		int mid = (L + R) / 2;
		if(L == R) return ;
		vector<int> l, r, cur;
		for(auto i : qs) {
			if(v[i].second <= mid) l.push_back(i);
			else if(v[i].first > mid) r.push_back(i);
			else cur.push_back(i);
		}
		qs.clear();
		rep(i, L, R) mx[i] = to[i] = val[i] = 0;
		// do left
		vector<int> st;
		st.push_back(mid + 1);
		int temp = a[mid + 1];
		a[mid + 1] = INF;
		rrep(i, L, mid) {
			int cnt = 0;
			while(st.size() && a[i] >= a[st.back()]) { 
				int lst = st.back(); st.pop_back();
				int pre = st.back();
				cnt += (pre - lst) * (a[i] - a[lst]) + val[lst] - val[pre];
			}
			cnt += val[st.back()];
			st.push_back(i);
			val[i] = cnt;
			mx[i] = max(mx[i + 1], a[i]);
		}
		a[mid + 1] = temp, mx[mid + 1] = temp;
		// do right
		rep(i, mid + 2, R) {
			val[i] = val[i - 1] + max(0ll, mx[i - 1] - a[i]);
			mx[i] = max(mx[i - 1], a[i]);
			if(a[i] > mx[i - 1]) to[i] = to[i - 1] + 
				(a[i] - mx[i - 1]) * (i - 1 - mid);
			else to[i] = to[i - 1] + mx[i] - a[i];
		}
		int rr= mid;
		rrep(i, L, mid) {
			while(rr < R && mx[i] > mx[rr + 1]) rr++;
			to[i] = rr;
		}
//		print(L, R);
//		rep(i, L, R) print(i, mx[i], val[i], to[i]);
		for(auto i : cur) {
			int l = v[i].first, r = v[i].second, tt = min(r, to[l]);
			if(tt > mid) {
				int cnt = val[l] + val[r] - val[tt] + 
					(tt - mid) * (mx[l] - mx[tt]) + to[tt];
				ans[i] = cnt;
			}
			else ans[i] = val[l] + val[r];
		}
		cur.clear();
		solve(L, mid, l);
		solve(mid + 1, R, r);
		return;
	}
}; 

using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	init_(n, q);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, q) cin >> v[i].first >> v[i].second;
	vector<int> tp;
	rep(i, 1, q) tp.push_back(i);
	solve(1, n, tp);
	rep(i, 1, q) cout << ans[i] << "\n";
	return 0;
}


