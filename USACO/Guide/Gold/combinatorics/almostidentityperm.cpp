#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ll n, k;
    cin >> n >> k;
    ll c = 0;
    if (k == 4)
        c += (n * (n - 1) * (n - 2) * (n - 3)) / 24 * 9, k--;
    if (k == 3)
        c += (n * (n - 1) * (n - 2)) / 6 * 2, k--;
    if (k == 2)
        c += (n * (n - 1)) / 2 * 1, k--;
    if (k == 1)
        k--;
    if (k == 0)
        c += 1, k--;
    cout << c << endl;
}