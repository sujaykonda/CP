#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
bool removed[100001];

int main()
{
    cin >> n;
    for (ll i = 1; i < n; i++)
        removed[i] = __gcd(n, i) != 1;
    ll modn = 1;
    for (ll i = 1; i < n; i++)
        if (!removed[i])
            modn = (modn * i) % n;
    if (modn == n - 1 && modn != 1)
        n--;
    ll s = 0;
    for (ll i = 1; i < n; i++)
        s += !removed[i];
    cout << s << endl;
    for (ll i = 1; i < n; i++)
        if (!removed[i])
            cout << i << " ";
    cout << endl;
}