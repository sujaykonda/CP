#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXX 1000001
#define modn 1000000007

ll fe(ll a, ll b, ll m)
{
    return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m);
}
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

int n;
vector<pair<ll, ll>> pf;
int main()
{
    cin >> n;
    pf.resize(n);
    for (int i = 0; i < n; i++)
        cin >> pf[i].first >> pf[i].second;
    ll num = 1;
    for (auto &[x, k] : pf)
        num = (num * (k + 1)) % modn;
    ll sum = 1;
    for (auto &[x, k] : pf)
    {
        ll geosum = ((fe(x, k + 1, modn) - 1) * minv(x - 1, modn)) % modn;
        sum = (sum * geosum) % modn;
    }

    vector<ll> suffix(n);
    suffix[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
        suffix[i] = (suffix[i + 1] * (pf[i + 1].second + 1)) % (modn - 1);
    vector<ll> prefix(n);
    prefix[0] = 1;
    for (int i = 1; i < n; i++)
        prefix[i] = (prefix[i - 1] * (pf[i - 1].second + 1)) % (modn - 1);

    ll prod = 1;
    for (int i = 0; i < n; i++)
    {
        ll asum = (((pf[i].second * (pf[i].second + 1)) / 2 % (modn - 1)) * ((prefix[i] * suffix[i]) % (modn - 1))) % (modn - 1);
        prod = (prod * fe(pf[i].first, asum, modn)) % modn;
    }
    cout << num << " " << sum << " " << prod << endl;
}