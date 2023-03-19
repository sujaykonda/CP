#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<pair<ll, int>> points;
int main()
{
    cin >> n;
    points.resize(2 * n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[2 * i].first >> points[2 * i + 1].first;
        points[2 * i].second = i, points[2 * i + 1].second = i;
        points[2 * i + 1].first++;
    }
    sort(points.begin(), points.end());
    vector<ll> cnt(n + 1);
    set<int> overlapping;
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (overlapping.count(points[i].second))
            overlapping.erase(points[i].second);
        else
            overlapping.insert(points[i].second);
        cnt[overlapping.size()] += points[i + 1].first - points[i].first;
    }
    for (int i = 1; i <= n; i++)
        cout << cnt[i] << " ";
    cout << endl;
}