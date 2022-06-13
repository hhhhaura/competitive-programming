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
	vector<vector<int>> S, T;
	vector<char> ch = {'A', 'T', 'C', 'G'};
	map<char, int> mp = {{'A', 0}, {'T', 1}, {'C', 2}, {'G', 3}};
	void solve(string s, string t) {
		vector<int> v;
		int n = s.size(), m = t.size();
		S.assign(4, vector<int>());
		T.assign(4, vector<int>());
		rep(i, 0, n - 1) S[mp[s[i]]].push_back(i);
		rep(i, 0, m - 1) T[mp[t[i]]].push_back(i);
		rep(i, 1, min(S[0].size(), T[0].size())) v.push_back(0);
		rep(bs, 1, 3) if(S[bs].size() && T[bs].size()) {
			int tot = v.size();
			vector<int> sufs(tot + 1, n), suft(tot + 1, m);
			rep(i, 1, tot) {
				int cur = v[tot - i], ii = sufs[i - 1] - 1;
				while(ii && s[ii] != ch[cur]) ii --;
				assert(s[ii] == ch[cur]);
				sufs[i] = ii;
			}
			rep(i, 1, tot) {
				int cur = v[tot - i], ii = suft[i - 1] - 1;
				while(ii && t[ii] != ch[cur]) ii --;
				assert(t[ii] == ch[cur]);
				suft[i] = ii;
			}
			vector<int> nxt;
			int L = 0, R = 0, ss = -1, tt = -1;
			while(L < S[bs].size() && R < T[bs].size() &&  
				S[bs][L] < sufs[tot] && T[bs][R] < suft[tot]) {
				ss = S[bs][L], tt = T[bs][R];
				L++, R++; 
				nxt.push_back(bs);
			}
		//	print(bs);
		//	vprint(all(sufs));
		//	vprint(all(suft));
			rep(i, 1, tot) {
				ss++, tt++;
				while(ss < n && s[ss] != ch[v[i - 1]]) ss++;
				while(tt < m && t[tt] != ch[v[i - 1]]) tt++;
				nxt.push_back(v[i - 1]);
				while(true) {
					while(L < S[bs].size() && S[bs][L] <= ss) L ++;
					while(R < T[bs].size() && T[bs][R] <= tt) R ++;
					if(L >= S[bs].size() || S[bs][L] >= sufs[tot - i]) break;
					if(R >= T[bs].size() || T[bs][R] >= suft[tot - i]) break;
					nxt.push_back(bs);
					ss = S[bs][L];
					tt = T[bs][R];
					L++, R++;
				}
			}
			v = nxt;
		}
		string ans = "";
		for(auto i : v) ans += ch[i];
		cout << ans << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string s, t; 
	cin >> s >> t;
	solve(s, t);
	return 0;
}

