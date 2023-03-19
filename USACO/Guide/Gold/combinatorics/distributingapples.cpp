#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 10000001
#define modn 1000000007
ll fe(ll a, ll b, ll m)
{
    return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m);
}
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

int main()
{
    factorials(maxn, modn);
    ll n, m;
    cin >> n >> m;
    cout << f[m + n - 1] * invf[n - 1] % modn * invf[m] % modn << endl;
}