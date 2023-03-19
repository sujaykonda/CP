#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m, q;
vector<ll> a;
vector<ll> b;
vector<ll> sb;
ll sa = 0;

ll solve()
{
    int i = lower_bound(sb.begin(), sb.end(), sa) - sb.begin();
    if (i == sb.size())
        i--;
    ll a = llabs(sb[i] - sa);
    if (i != sb.size() - 1)
        a = min(a, llabs(sb[i + 1] - sa));
    if (i != 0)
        a = min(a, llabs(sb[i - 1] - sa));

    return a;
}

int main()
{
    cin >> n >> m >> q;
    a.resize(n + 1);
    b.resize(m + 1);
    sb.resize(m - n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i], sa += (2 * (i % 2) - 1) * a[i];
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        sb[0] += (2 * (i % 2) - 1) * b[i];
    for (int i = 1; i <= m - n; i++)
        sb[i] = -sb[i - 1] + b[i] + (2 * (n % 2) - 1) * b[i + n];
    sort(sb.begin(), sb.end());
    cout << solve() << endl;
    while (q--)
    {
        ll l, r, x;
        cin >> l >> r >> x;
        if ((l % 2) == (r % 2))
            sa += (2 * (l % 2) - 1) * x;
        cout << solve() << endl;
    }
}