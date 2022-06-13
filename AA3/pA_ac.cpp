#include<iostream>
#include<algorithm>
#include<cstring>
#define SZ(X) ((int)(X).size())
#define MP make_pair
#define PII pair<int, int>
#define PB push_back
#define F first
#define S second
using namespace std;
const int MAX_SIZE = 200001;
int n;
int x[MAX_SIZE];
void handle(int &r, int p, PII & now) {
    int tmp = p;
    PII info{1, 0};
    if(x[p] != -1) info = {p, x[p]};
    while((r / tmp) % p == 0) {
        tmp *= p;
        if(x[tmp] != -1) info = {tmp, x[tmp]};
    }
    r /= tmp;
    if(info.F > now.F) swap(info, now);
    int ans = -1;
    for(int i = 0 ; i < info.F; i++) {
        if((now.F * i + now.S) % info.F == info.S) {
            ans = now.F * i + now.S;
        }
    }
    now = {now.F * info.F, ans};
}
void add_new_info(int &r, int p, int v) {
    int tmp = 1;
    do{
        tmp *= p;
        x[tmp] = v % tmp;
    } while((r / tmp) % p == 0);
    r /= tmp;
}
void add(int r, int v) {
    int tmp_r = r;
    PII now{1, 0};
    for(int i = 2; i * i <= r; i++) {
        if(r % i == 0) {
            handle(r, i, now);
        }
    }
    if(r != 1) {
        handle(r, r, now);
    }

    if(v % now.F != now.S) v = now.S;
    cout << tmp_r << ' ' << v << '\n';
    for(int i = 2; i * i <= tmp_r; i++) {
        if(tmp_r % i == 0) {
            add_new_info(tmp_r, i, v);
        }
    }
    if(tmp_r != 1) {
        add_new_info(tmp_r, tmp_r, v);
    }
}
void solve() {
    cin >> n;
    memset(x, -1, sizeof(int) * MAX_SIZE);
    for(int i = 0; i < n; i++) {
        int r, v;
        cin >> r >> v;
        add(r, v);
    }
}
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
