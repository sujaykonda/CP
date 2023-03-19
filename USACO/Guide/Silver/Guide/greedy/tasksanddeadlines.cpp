#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
vector<pair<ll, ll>> a;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >>
            a[i].first >> a[i].second;
    sort(a.begin(), a.end());

    ll r = 0;
    ll t = 0;
    for (int i = 0; i < n; i++)
    {
        t += a[i].first;
        r += a[i].second - t;
    }
    cout << r << endl;
}