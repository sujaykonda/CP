#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

vector<ll> f;
vector<ll> invf;

void factorials(ll mx, ll m)
{
    f.resize(mx);
    invf.resize(mx);
    f[0] = 1, invf[0] = 1;
    for (int i = 1; i < mx; i++)
        f[i] = (f[i - 1] * i) % m;
    invf[mx - 1] = minv(f[mx - 1], m);
    for (int i = mx - 1; i >= 1; i--)
        invf[i - 1] = (invf[i] * i) % m;
}


int main() {
    int n; cin >> n;
    vector<vector<ll>> dp(n);
}

// 16 * 2 * (2 choose 3) * (2^2)! + 8 * 2 * (2 choose 2) * 4 * (2^2)!
// 16 * 2 * (5 choose 3) * (2^2)! + 8 * 2 * (5 choose 2) * (2^2)!