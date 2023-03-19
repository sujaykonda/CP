#include <bits/stdc++.h>
using namespace std;
#define ll long long

int t;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int test = 0; test < t; test++)
    {
        int n;
        cin >> n;
        vector<ll> d(2 * n);
        for (int i = 0; i < 2 * n; i++)
            cin >> d[i];

        sort(d.begin(), d.end(), greater<ll>());
        set<ll> a;
        bool good = true;
        ll p = 0;
        for (int i = 0; i < 2 * n; i += 2)
        {
            if (d[i] != d[i + 1])
                good = false;
            else if ((d[i] - p) % (2 * n - i) != 0)
                good = false;
            else if ((d[i] - p) / (2 * n - i) <= 0)
                good = false;
            else if (a.count((d[i] - p) / (2 * n - i)))
                good = false;
            if (!good)
                break;
            // cout << (d[i] - p) / (2 * n - i) << " ";
            a.insert((d[i] - p) / (2 * n - i));
            p += (d[i] - p) / (2 * n - i) * 2;
        }
        if (good)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}