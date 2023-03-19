#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N;

vector<pair<int, int>> cows;

ll bs(ll lo, ll hi, function<bool(ll)> f)
{
    hi++;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo) / 2;
        if (f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

bitset<1001> comp;

void dfs(int s, ll X)
{
    if (comp[s] == 1)
        return;
    comp[s] = 1;
    for (int i = 0; i < N; i++)
    {
        ll dist = pow((cows[s].first - cows[i].first), 2) + pow((cows[s].second - cows[i].second), 2);
        if (dist <= X)
            dfs(i, X);
    }
}

bool check(ll X)
{
    comp.reset();
    dfs(0, X);
    for (int i = 0; i < N; i++)
        if (!comp[i])
            return false;
    return true;
}

int main()
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    cin >> N;
    cows.resize(N);
    for (int i = 0; i < N; i++)
        cin >> cows[i].first >> cows[i].second;
    cout << bs(0, 1250000000, check) << endl;
}