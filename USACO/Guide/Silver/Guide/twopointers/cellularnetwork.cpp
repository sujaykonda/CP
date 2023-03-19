#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, m;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll ma = 0;
    for (int i = 0, j = 0; i < n; i++)
    {
        while ((j + 1) < m && (abs(a[i] - b[j]) >= abs(a[i] - b[j + 1])))
            j++;
        ma = max(ma, abs(a[i] - b[j]));
    }
    cout << ma << endl;
}