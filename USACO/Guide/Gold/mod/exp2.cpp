#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll modn = 1000000007;
ll fe(ll a, ll b)
{
    return b == 0 ? 1 : (((fe((a * a) % modn, b / 2) % modn) * ((b % 2 ? a : 1) % modn)) % modn);
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        modn--;
        ll bc = fe(b, c);
        modn++;
        cout << fe(a, bc) << endl;
    }
}