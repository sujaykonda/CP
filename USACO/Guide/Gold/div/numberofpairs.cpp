#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 20000001

ll lpf[MAXN];
ll pfc[MAXN];

void sieve()
{
    for (ll i = 1; i < MAXN; i++)
        lpf[i] = i;
    for (ll i = 2; i < MAXN; i++)
        if (lpf[i] == i)
            for (ll j = i; j < MAXN; j += i)
                lpf[j] = i;
}

void pfcbuild()
{
    for (ll i = 2; i < MAXN; i++)
        pfc[i] = pfc[i / lpf[i]] + ((i / lpf[i]) % lpf[i] != 0);
}

int main()
{
    sieve();
    pfcbuild();
    int t;
    cin >> t;
    while (t--)
    {
        ll c, d, x;
        ll cnt = 0;
        cin >> c >> d >> x;
        for (ll i = 1; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                if ((i + d) % c == 0)
                    cnt += 1 << pfc[(i + d) / c];
                if (i * i == x)
                    continue;
                if ((x / i + d) % c == 0)
                    cnt += 1 << pfc[(x / i + d) / c];
            }
        }
        cout << cnt << endl;
    }
}