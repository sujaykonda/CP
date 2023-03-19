// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll N;
vector<ll> c;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);
    cin >> N;
    c.resize(N);
    for (int i = 0; i < N; i++)
        cin >> c[i];

    sort(c.begin(), c.end());
    ll ma = max(c[N - 2] - c[0] - N + 2, c[N - 1] - c[1] - N + 2);
    ll mi = ma;
    for (int i = 0, j = 0; i < N; i++)
    {
        while (j + 1 < N && c[j + 1] < c[i] + N)
            j++;
        mi = min(mi, N + i - j - 1);
    }
    if (c[N - 2] - c[0] == N - 2 && c[N - 1] - c[N - 2] > 2)
        mi = 2;
    if (c[N - 1] - c[1] == N - 2 && c[1] - c[0] > 2)
        mi = 2;
    cout << mi << "\n"
         << ma << "\n";
    return 0;
}
