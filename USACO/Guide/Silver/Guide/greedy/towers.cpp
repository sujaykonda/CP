#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
vector<ll> k;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    k.resize(n);
    for (int i = 0; i < n; i++)
        cin >> k[i];

    vector<ll> ts;
    for (int i = 0; i < n; i++)
    {
        auto p = upper_bound(ts.begin(), ts.end(), k[i]);
        if (p == ts.end())
            ts.push_back(k[i]);
        else
            *p = k[i];
    }
    cout << ts.size() << endl;
}