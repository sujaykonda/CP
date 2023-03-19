#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define inf 1000000

struct State
{
    ll i, j, d;
};

vector<vector<ll>> dp;

int main()
{
    int t, n;
    cin >> t >> n;

    dp.resize(1 << n, vector<ll>(1 << n, inf));

    queue<State> q;
    for (int j = 0; j < (1 << n); j++)
    {
        State s;
        s.i = 0, s.j = j, s.d = 0;
        q.push(s);
    }

    while (!q.empty())
    {
        State s = q.front();
        q.pop();
        if (dp[s.i][s.j] <= s.d)
            continue;
        cout << bitset<10>(s.i) << " " << bitset<10>(s.j) << " " << s.d << endl;
        dp[s.i][s.j] = s.d;
        for (ll k = 0; k < n; k++)
        {
            State ns;
            ns.j = (s.j >> 1) + ((s.j & 1) << (n - 1));
            ns.i = s.i ^ ns.j;
            ns.j ^= (1 << k);
            ns.d = s.d + 1;
            q.push(ns);
        }
    }

    while (t--)
    {
        string a, b;
        cin >> a >> b;
        ll p = 1;
        ll ai = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            ai += p * (a[i] == '1');
            p *= 2;
        }
        p = 1;
        ll bi = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            bi += p * (b[i] == '1');
            p *= 2;
        }
        cout << dp[ai][bi] << endl;
    }
}