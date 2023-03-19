#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, x;
vector<pair<ll, ll>> a;

void solve()
{
    for (int k = 0; k < n; k++)
    {
        ll t = x - a[k].first;
        int i = 0;
        int j = n - 1;
        while (i != j)
        {
            if (a[i].first + a[j].first < t)
            {
                i++;
                continue;
            }
            if (a[i].first + a[j].first > t)
            {
                j--;
                continue;
            }
            if (i == j || j == k || i == k)
            {
                i++;
                continue;
            }
            cout << a[i].second << " " << a[j].second << " " << a[k].second << endl;
            return;
        }
    }
    cout << "IMPOSSIBLE" << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;

    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a.begin(), a.end());
    solve();
}