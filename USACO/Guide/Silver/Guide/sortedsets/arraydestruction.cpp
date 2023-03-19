#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 2000;

int n;
int a[MAX_SIZE];

vector<pair<int, int>> pair_to_remove;

bool works(int x)
{
    pair_to_remove.clear();
    // This multiset stores the all of the undestroyed elements
    multiset<int> remaining;
    for (int i = 0; i < n; i++)
    {
        remaining.insert(a[i]);
    }
    while (remaining.size())
    {
        // The largest element that hasn't been removed
        int c = *remaining.rbegin();
        remaining.erase(remaining.find(c));
        // If this condition is true, then it is impossible to destruct the array with the given initial sum
        if (remaining.find(x - c) == remaining.end())
        {
            return false;
        }
        remaining.erase(remaining.find(x - c));
        pair_to_remove.push_back({c, x - c});
        x = c;
    }
    return remaining.empty();
}

void solve()
{
    cin >> n;
    n *= 2;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++)
    {
        int x = a[i] + a[n - 1];
        if (works(x))
        {
            cout << "YES" << endl;
            cout << x << endl;
            for (pair<int, int> x : pair_to_remove)
                cout << x.first << " " << x.second << endl;
            return;
        }
    }
    cout << "NO" << endl;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
        solve();
}