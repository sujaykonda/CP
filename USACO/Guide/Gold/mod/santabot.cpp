#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 998244353

ll fe(ll a, ll b, ll m)
{
    return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m);
}
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

int n;
vector<vector<int>> a;
unordered_map<int, int> afreq;

int main()
{
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++)
            cin >> a[i][j], afreq[a[i][j]]++;
    }
    ll frac = 0;
    for (int i = 0; i < n; i++)
    {
        for (int aij : a[i])
        {
            ll c = afreq[aij] % modn;
            ll d = ((n * (ll)a[i].size()) % modn * n) % modn;
            frac = (frac % modn + (c * minv(d, modn)) % modn) % modn;
        }
    }
    cout << frac << endl;
}