#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, k;
vector<pair<ll, ll>> e;
multiset<ll> ts;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    e.resize(n);
    for (int i = 0; i < n; i++)
        cin >> e[i].second >> e[i].first;

    sort(e.begin(), e.end());
    for (int i = 0; i < k; i++)
        ts.insert(0);
    ll m = 0;
    for (pair<ll, ll> ei : e)
    {
        auto p = ts.upper_bound(ei.second);
        if (p != ts.begin())
        {
            ts.erase(--p);
            ts.insert(ei.first);
            m++;
        }
    }
    cout << m << endl;
}