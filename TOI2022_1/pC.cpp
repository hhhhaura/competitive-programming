#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define INF 1000000000000000000
#define eps (1e-9)
using namespace std;
#ifdef wiwihorz
#define print(a...)cerr<<"Line "<<__LINE__<<":",kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, p;
	cin >> n >> m;
	vector<string> a(n, "");
	const int P = 2000001;
	map<pii, int> cnt;
	vector<pii> pre(P, {1, 1}), inv(P, {1, 1});
	const pii w = {31, 47};
	const pii MOD = {998244353, 1000000007};
	auto pow_ = [](int a, int times, int MOD) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	};
	pii iw = {pow_(w.x, MOD.x - 2, MOD.x), 
		pow_(w.y, MOD.y - 2, MOD.y) };
	rep(i, 1, P - 1) {
		pre[i].x = pre[i - 1].x * w.x % MOD.x;
		pre[i].y = pre[i - 1].y * w.y % MOD.y;
	}	
	rep(i, 1, P - 1) {
		inv[i].x = inv[i - 1].x * iw.x % MOD.x;
		inv[i].y = inv[i - 1].y * iw.y % MOD.y;
	}
	auto get_seg = [&](vector<pii> &v, int L, int R) {
		pii ans = {
			(v[R].x - v[L - 1].x + MOD.x) % MOD.x,
			(v[R].y - v[L - 1].y + MOD.y) % MOD.y
		};
		ans.x = (ans.x * inv[L - 1].x) % MOD.x;
		ans.y = (ans.y * inv[L - 1].y) % MOD.y;
		return ans;
	};
	rep(i, 0, n - 1) cin >> a[i];
	sort(all(a), [&](string a, string b) {
		return a.size() < b.size();
	});
	int ans = 0;
	rep(i, 0, n - 1) {
		int len = a[i].size();
		string s = a[i];
		vector<pii> v(len + 1, {0, 0});
		vector<pii> iv(len + 1, {0, 0});
		rep(j, 1, len) {
			int pos = s[j - 1] - 'a' + 1;
			v[j].x = (v[j - 1].x + pos * pre[j].x % MOD.x) % MOD.x;
			v[j].y = (v[j - 1].y + pos * pre[j].y % MOD.y) % MOD.y;
		}
		rep(j, 1, len) {
			int pos = s[len - j] - 'a' + 1;
			iv[j].x = (iv[j - 1].x + pos * pre[j].x % MOD.x) % MOD.x;
			iv[j].y = (iv[j - 1].y + pos * pre[j].y % MOD.y) % MOD.y;
		}
		ans += cnt[v[len]];
		rep(j, 1, len - 1) {
			if(get_seg(v, 1, j) != get_seg(iv, len - j + 1, len)) continue;
			ans += cnt[get_seg(v, j + 1, len)];
		}
		rep(j, 1, len - 1) {
			if(get_seg(v, len - j + 1, len) != get_seg(iv, 1, j)) continue;
			if(get_seg(v, 1, len - j) == get_seg(v, j + 1, len) &&
				get_seg(v, 1, j) == get_seg(iv, len - j + 1, len)) continue;
			ans += cnt[get_seg(v, 1, len - j)];
		}
		cnt[iv[len]] ++;
	} 
	cout << ans << "\n";
	return 0;
}

