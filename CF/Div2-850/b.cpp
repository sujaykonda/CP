#include <bits/stdc++.h>
using namespace std;
 
void testcase()
{
    int n, w, h;
    cin >> n >> w >> h;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 1; i < n; i++)
        a[i] -= a[0], b[i] -= b[0];
    a[0] = b[0] = 0;
    int L = h - w;
    int R = w - h;
    for (int i = 0; i < n; i++)
    {
        L = max(L, (a[i] - w) - (b[i] - h));
        R = min(R, (a[i] + w) - (b[i] + h));
    }
    if (L > R)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
}
 
int main()
{
    int t;
    cin >> t;
    while (t--)
        testcase();
}