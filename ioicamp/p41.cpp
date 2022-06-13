#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 106;

ll f[N];

int main () {
  ll n, y, p, m; cin >> n >> f[0] >> f[1] >> y >> p >> m;
  for (int i = 2; i <= n; ++i) {
    f[i] = (y * f[i - 1] - p * f[i - 2]) % m;
  	cerr << "i " << i << " "<< f[i] << "\n";
  }
  cout << f[n] << endl;
}
