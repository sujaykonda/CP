#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
void testcase()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    ll cost = 0;
    ll p = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > p)
            p++;
        cost += a[i] - p;
    }
    cout << cost << endl;
}
 
int main()
{
    int t;
    cin >> t;
    while (t--)
        testcase();
}