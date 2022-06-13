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
#define x first
#define y second
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, x;
	cin >> n >> x;
	const int P = 100000;
	vector<int> cur, nxt;
	vector<int> C(n + 1, 0), V(n + 1, 0), N(n + 1, 0);
	rep(i, 1, n) cin >> C[i];
	rep(i, 1, n) cin >> V[i];
	rep(i, 1, n) cin >> N[i];
	cur.assign(P + 1, 0);
	cur[0] = 0;
	rep(i, 1, n) {
		nxt.assign(P + 1, 0);
		rep(j, 0, C[i] - 1) {
			deque<pii> q;
			for(int k = j; k <= P; k += C[i]) {
				pii p = {k, cur[k] - V[i] * (k / C[i])};
				while(q.size() && q.back().y <= p.y) q.pop_back();
				q.push_back(p);
				while(q.size() && q.front().x < k - N[i] * C[i]) q.pop_front();
				assert(q.size());
				nxt[k] = q.front().y + V[i] * (k / C[i]);
			}
		}	
		cur = nxt;
	}
	cout << cur[x] << "\n";
	return 0;
}


