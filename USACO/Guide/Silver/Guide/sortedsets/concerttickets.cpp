#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
int main()
{
    cin >> n >> m;

    multiset<ll> prices;
    for (int i = 0; i < n; i++)
    {
        int h;
        cin >> h;
        prices.insert(-h);
    }
    for (int i = 0; i < m; i++)
    {
        int t;
        cin >> t;
        if (prices.lower_bound(-t) == prices.end())
            cout << "-1\n";
        else
        {
            ll p = -*prices.lower_bound(-t);
            prices.erase(prices.lower_bound(-t));
            cout << p << "\n";
        }
    }
}