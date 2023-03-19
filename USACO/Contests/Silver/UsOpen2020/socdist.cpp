#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll N, M;
vector<ll> grass;

ll bs(ll lo, ll hi, function<bool(ll)> f)
{
    while (lo < hi)
    {
        ll mid = lo + (hi - lo) / 2;
        if (f(mid))
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

bool check(ll D)
{
    ll p = grass[0];
    for (int n = 1; n < N; n++)
    {
        int i = lower_bound(grass.begin(), grass.end(), p + D) - grass.begin();
        if (i == 2 * M)
            return false;
        if (i % 2 == 0)
        {
            p = grass[i];
        }
        else
        {
            p = max(p + D, grass[i - 1]);
        }
    }
    return true;
}

int main()
{
    cin >> N >> M;
    grass.resize(2 * M);
    for (int i = 0; i < M; i++)
        cin >> grass[2 * i] >> grass[2 * i + 1];

    sort(grass.begin(), grass.end());
    cout << bs(0, grass[2 * M - 1], check) - 1 << endl;
}