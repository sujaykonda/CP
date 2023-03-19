#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, x;
vector<ll> p;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;
    p.resize(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];

    sort(p.begin(), p.end());

    ll c = 0;
    int i = 0;
    int j = n - 1;
    while (i <= j)
    {
        if (j > 0 && p[i] + p[j] > x)
        {
            j--, c++;
            continue;
        }
        j--;
        i++;
        c++;
    }
    cout << c << endl;
}