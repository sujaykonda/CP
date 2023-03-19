#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 998244353

ll fe(ll a, ll b, ll m)
{
    return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m);
}
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

int Q;
ll a = 1;
ll b = 0;
queue<pair<ll, ll>> f;

int main()
{
    cin >> Q;
    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            ll a2, b2;
            cin >> a2 >> b2;
            f.push({a2, b2});
            a = (a * a2) % modn;
            b = ((a2 * b) % modn + b2) % modn;
        }
        else if (t == 1)
        {
            a = (a * minv(f.front().first, modn)) % modn;
            b = (b - (a * f.front().second) % modn) % modn;
            if (b < 0)
                b += modn;
            f.pop();
        }
        else
        {
            ll x;
            cin >> x;
            cout << ((a * x) % modn + b % modn) % modn << endl;
        }
    }
}