#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, m, k;
vector<ll> a;
vector<ll> b;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    a.resize(n);
    b.resize(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll m = 0;
    int i = 0;
    int j = 0;
    while (i < a.size() && j < b.size())
    {
        if (a[i] < b[j] - k)
        {
            i++;
            continue;
        }
        if (a[i] > b[j] + k)
            j++;
        else
            i++, j++, m++;
    }
    cout << m << endl;
}