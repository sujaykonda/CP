#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 1000000007
ll n;

ll calcS(ll i)
{
    ll sl = (n / i - n / (i + 1)) % modn;
    return ((((sl * sl - sl) / 2 % modn) * i) + (n % i * sl) % modn) % modn;
}

int main()
{
    cin >> n;
    ll s = (n % modn) * (n % modn) % modn;
    for (ll i = 1; i * i <= n; i++)
    {
        s = (s - calcS(i) - calcS(n / i)) % modn;
        if (n / (n / i) == n / i)
            s = (s + calcS(n / i)) % modn;
    }
    if (s < 0)
        s += modn;
    cout << s << endl;
}