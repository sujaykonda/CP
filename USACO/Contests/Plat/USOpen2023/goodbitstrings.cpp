#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll inv(ll A, ll M)
{
    ll m0 = M;
    __int128_t y = 0, x = 1;
 
    if (M == 1)
        return 0;
 
    while (A > 1) {
        __int128_t q = A / M;
        __int128_t t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;
 
    return x;
}

ll solve(ll a, ll b, ll c, ll d) {
    if((__int128_t)a * d > (__int128_t)b * c) {
        swap(a, c);
        swap(b, d);
    }
    if(a == 0 && d == 0) {
        return b + c;
    }
    if(d >= b) {
        return d / b + solve(a, b, c - a * (d / b), d - b * (d / b));
    } else {
        ll ad = -c * (a / c);
        ll bd = -d * (a / c);
        return a / c + (a + ad == 0 ? 0 : min((a + ad + c) / (a + ad), (b + bd + d) / (b + bd)) - 1) + solve(a + ad, b + bd, c, d);
    }    
}

int main() {
    int T; cin >> T;
    for(int t = 0; t < T; t++) {
        ll x, y; cin >> x >> y; 
        ll g = gcd(x, y);
        ll ans = 0;
        if(y / g == 1) {
            ans = x / g;
        } else if(x / g == 1) {
            ans = y / g;
        } else {
            //cout << x / g << " " << y / g << endl;
            ll b = inv((x / g) % (y / g), y / g);
            ll a = ((__int128_t)x * b) / y;
            ll c = x / g - a, d = y / g - b;
            ans = solve(a, b, c, d) + (y / g) / b - 2;
        }
        cout << 2 * (g - 1) + ans << '\n';
    }
}