#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#pragma GCC target("sse")

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(a) a.begin(), a.end()
#define ceil(a, b) ((a + b - 1) / (b))

using namespace std;

#define int long long int
#define pii pair<int, int>
#define lld long double
#define eps (1e-9)
#define INF 1000000000000000000
#define MOD 1000000007
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) cerr<<"Line "<<__LINE__<<": ", kout("["+string(#a)+"] = ",a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a,T2 ... e){cerr<<a<<" ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, ans;
	vector<int> a, cnt;
	vector<pii> ops;
	set<pii> s;
	void init_(int _n) {
		n = _n, ans = 0;
		a.assign(n + 1, 0);
		cnt.assign(n + 2, 0); // i - 1 -> i
		ops.clear();
		s.clear();
	}
	int operate(int tp, int x, int op) {
		if(op == 1) { // insert
			auto R = s.lower_bound({x, -INF});
			auto L = (R == s.begin() ? s.end() : prev(R));
			s.insert({x, tp});
			if(L == s.end() && R == s.end()) return 1;
			else if(L == s.end()) ans += (tp == 0 && R -> second == 1);
			else if(R == s.end()) ans += (tp == 1 && L -> second == 0);
			else ans += (L -> second != tp && R -> second != tp);
		}
		else {
			auto cur = s.find({x, tp});
			auto L = (cur == s.begin() ? s.end() : prev(cur));
			auto R = next(cur);
			s.erase(cur);
			if(L == s.end() && R == s.end()) return 1;
			else if(L == s.end()) ans -= (tp == 0 && R -> second == 1);
			else if(R == s.end()) ans -= (tp == 1 && L -> second == 0);
			else ans -= (L -> second != tp && R -> second != tp);
		}
		return 1;
	}
	void solve() {
		set<int> num;
		vector<pii> val;
		rep(i, 1, n) val.push_back({a[i], i});
		sort(all(val)), reverse(all(val));
		for(auto i : val) {
			auto it = num.lower_bound(i.second);
			while(it != num.end()) {
				cnt[i.first] += operate(0, *it, 0);
				ops.push_back({*it, 1});
				auto temp = it;
				it = next(it);
				num.erase(temp);
			}
			cnt[i.first] += operate(0, i.second, 1);
			ops.push_back({i.second, 0});
			num.insert(i.second);
		}
		reverse(all(val));
		num.clear();
		cout << 0 << "\n";
		for(auto i : val) {
			rep(j, 1, cnt[i.first]) {
				pii p = ops.back(); ops.pop_back();
				operate(0, p.first, p.second);
			}
			auto it = num.lower_bound(i.second);
			while(it != num.end()) {
				operate(1, *it, 0);
				auto temp = it;
				it = next(it);
				num.erase(temp);
			}
			num.insert(i.second);
			operate(1, i.second, 1);
			cout << ans << "\n";
		}
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie();
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	solve();
	return 0;
}

