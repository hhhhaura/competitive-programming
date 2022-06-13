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
namespace solver {
	random;
	string s;
	int n, m, ii = 0, root = 0;
	const int P = 200001;
	struct node { int pri, val, sum, l, r, sz, rev; };
	struct seg { int l, mid, r; };
	vector<node> v(P + 1, {0, 0, 0, 0, 0, 0, 0});
	int get_new(int val) {
		v[++ii] = {rnd(), val, val, 0, 0, 1, 0};
		return ii;
	}
	void push(int cur) {
		int l = v[cur].l, r = v[cur].r;
		if(v[cur].rev) {
			v[l].rev ^= 1;
			v[r].rev ^= 1;
			swap(v[l].l, v[l].r);
			swap(v[r].l, v[r].r);
			v[cur].rev = 0;
		}
	}
	void pull(int cur) {
		int l = v[cur].l, r = v[cur].r;
		v[cur].sz = 1 + v[l].sz + v[r].sz;
		v[cur].sum = v[cur].val + v[l].sum + v[r].sum;
	}
	int merge(int pre, int suf) {
		if(!pre) return suf;
		if(!suf) return pre;
		if(v[pre].pri > v[suf].pri) {
			push(pre);
			v[pre].r = merge(v[pre].r, suf);
			pull(pre);
			return pre;
		}
		else {
			push(suf);
			v[suf].l = merge(pre, v[suf].l);
			pull(suf);
			return suf;
		}
	}
	pii split(int cur, int k) {
		if(!cur) return {0, 0};
		push(cur);
		int l = v[cur].l, r = v[cur].r;
		if(k <= v[l].sz) {
			pii p = split(l, k);
			v[cur].l = p.second;
			pull(cur);
			return {p.first, cur};
		}
		else {
			pii p = split(r, k - v[l].sz - 1);
			v[cur].r = p.first;
			pull(cur);
			return {cur, p.second};
		}
	}
	seg get_seg(int L, int R) {
		pii p = split(root, R);
		pii p1 = split(p.first, L - 1);
		return {p1.first, p1.second, p.second};
	}
	void solve(int n, int m) {
		rep(i, 1, n) {
			int x; cin >> x;
			root = merge(root, get_new(x));
		}
		rep(i, 1, m) {
			int tp, a, b; 
			cin >> tp >> a >> b;
			seg cur = get_seg(a, b);
			if(tp == 1) {
				v[cur.mid].rev ^= 1;
				swap(v[cur.mid].l, v[cur.mid].r);
			}
			else cout << v[cur.mid].sum << "\n";
			root = merge(cur.l, merge(cur.mid, cur.r));
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	solve(n, m);
	return 0;
}




