#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
vector<ll> a;

ll P[100001];
ll S[100001];

int main()
{
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    P[0] = a[0];
    for (int i = 1; i < n; i++)
        P[i] = __gcd(P[i - 1], a[i]);
    S[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--)
        S[i] = __gcd(S[i + 1], a[i]);

    ll d = __gcd((a[0] * S[1]) / S[0], (a[n - 1] * P[n - 2]) / S[0]);
    for (int i = 1; i < n - 1; i++)
    {
        d = __gcd(d, (a[i] * __gcd(P[i - 1], S[i + 1])) / S[0]);
    }
    cout << d << endl;
}