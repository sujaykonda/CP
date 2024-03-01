#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MX = 2e6 + 2;
const int MOD = 998244353;
int fac[MX];
int ifac[MX];

int bpow(int a, int b) {
    return b == 0 ? 1 : ((ll)bpow(((ll)a * a) % MOD, b / 2) * ((b % 2) ? a : 1)) % MOD;
}

void tc() {
    int c1, c2, c3, c4; cin >> c1 >> c2 >> c3 >> c4;
    if(abs(c1 - c2) == 1) {
        int cnt = (c1 + c2 + 1) / 2;
        int a1 = ((ll)(((ll)fac[cnt + c3 - 1] * ifac[cnt - 1]) % MOD) * ifac[c3]) % MOD;
        int a2 = ((ll)(((ll)fac[cnt + c4 - 1] * ifac[cnt - 1]) % MOD) * ifac[c4]) % MOD;
        cout << ((ll)a1 * a2) % MOD << '\n';;
    } else if(c1 == c2) {
        if(c1 == 0) {
            if(!((c3 > 0) && (c4 > 0))) cout << 1 << '\n';
            else cout << 0 << '\n';
        } else {
            int b = (c1 + c2) / 2;
            int a1 = ((ll)(((ll)fac[b + c3 - 1] * ifac[b - 1]) % MOD) * ifac[c3]) % MOD;
            int a2 = ((ll)(((ll)fac[b + c4] * ifac[b]) % MOD) * ifac[c4]) % MOD;
            int a3 = ((ll)(((ll)fac[b + c3] * ifac[b]) % MOD) * ifac[c3]) % MOD;
            int a4 = ((ll)(((ll)fac[b + c4 - 1] * ifac[b - 1]) % MOD) * ifac[c4]) % MOD;
            cout << ((ll)a1 * a2 + (ll)a3 * a4) % MOD << '\n';;
        }
    } else {        
        cout << 0 << '\n';
    }

}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    fac[0] = 1;
    for(int i = 1; i < MX; i++) {
        fac[i] = ((ll)fac[i - 1] * i) % MOD;
    }
    ifac[MX - 1] = bpow(fac[MX - 1], MOD - 2);
    for(int i = MX - 1; i >= 1; i--) {
        ifac[i - 1] = ((ll)ifac[i] * i) % MOD;
    }
    int t; cin >> t;
    while(t--) {
        tc();
    }
}