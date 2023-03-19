#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<int, int>> c;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    c.resize(2 * n);
    for (int i = 0; i < n; i++)
    {
        cin >> c[2 * i].first >> c[2 * i + 1].first;
        c[2 * i].second = 1;
        c[2 * i + 1].second = -1;
    }
    int m = 0;
    int p = 0;
    sort(c.begin(), c.end());
    for (int i = 0; i < c.size(); i++)
    {
        p += c[i].second;
        m = max(m, p);
    }
    cout << m << endl;
}