#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
int fpow(int x, ll y) { return y == 0 ? 1 : (ll)fpow((ll)x * x % MOD, y / 2) * (y & 1 ? x : 1) % MOD; }


int main() {
    int N, x; cin >> N >> x;
    vector<int> inv(N + 1);
    for(int i = 1; i <= N; i++) inv[i] = fpow(i, MOD - 2);
    vector<int> pr(x + 1), pc(N + 1 - x);
    int totep = 0;
    for(int i = 0; i <= x; i++) {
        for(int j = 0; j <= N - x; j++) {
            int loep = ((ll)(pr[i] + pc[j]) * inv[i + j]) % MOD;
            int hiep = (loep + (ll)i * inv[i + j]) % MOD;
            if(i < x || j < N - x) {
                pr[i] = (pr[i] + hiep) % MOD;
                pc[j] = (pc[j] + loep) % MOD;
            } else {
                totep = loep;
            }
        }
    }
    int fac = 1;
    for(int i = 2; i <= N; i++) fac = ((ll)fac * i) % MOD;
    cout << ((ll)totep * fac) % MOD << endl;
}