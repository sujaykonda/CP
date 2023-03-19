#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
vector<ll> p;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    sort(p.begin(), p.end());
    ll med = p[n / 2];
    ll s = 0;
    for (int i = 0; i < n; i++)
        s += abs(med - p[i]);
    cout << s << endl;
}