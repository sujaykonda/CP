#include <bits/stdc++.h>
using namespace std;
#define ll long long
bool cmp(pair<pair<ll, ll>, int> a, pair<pair<ll, ll>, int> b)
{
    if (a.first.second == b.first.second)
    {
        return a.first.first > b.first.first;
    }
    else
    {
        return a.first.second < b.first.second;
    }
}

int t;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int test = 0; test < t; test++)
    {
        int n;
        cin >> n;
        vector<pair<pair<ll, ll>, int>> f(n);
        for (int i = 0; i < n; i++)
        {
            cin >> f[i].first.first >> f[i].first.second;
            if (f[i].first.first > f[i].first.second)
                f[i].first = {f[i].first.second, f[i].first.first};
            f[i].second = i + 1;
        }
        sort(f.begin(), f.end(), cmp);
        vector<int> ans(n + 1, -1);
        for (int i = 1, j = 0; i < n; i++)
        {
            // cout << f[i].first.first << " " << f[i].first.second << " " << f[i].second << " ";
            // cout << f[j].first.first << " " << f[j].first.second << " " << f[j].second << endl;
            if (f[i].first.first > f[j].first.first)
                ans[f[i].second] = f[j].second;
            else
                j = i;
        }
        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}