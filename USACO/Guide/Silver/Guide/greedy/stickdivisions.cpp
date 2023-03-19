#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll x, n;
vector<ll> s;
vector<ll> p;

ll solve(int s, int e)
{
    // cout << s << " " << e << endl;
    if (s + 1 == e)
        return 0;
    ll best = INT_MAX;
    for (int i = s + 1; i < e; i++)
    {
        best = min(best, solve(s, i) + solve(i, e));
    }
    return p[e] - p[s] + best;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> n;
    s.resize(n);
    p.resize(n + 1);
    for (int i = 0; i < n; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++)
        p[i] = p[i - 1] + s[i - 1];

    sort(s.begin(), s.end());
    cout << solve(0, n) << endl;
}