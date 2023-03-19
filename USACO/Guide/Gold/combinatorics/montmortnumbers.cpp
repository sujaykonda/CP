#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ll N, M;
    cin >> N >> M;
    ll c = 1;
    for (int i = 1; i <= N; i++)
    {
        c = (i * c + (-2 * (i % 2) + 1)) % M;
        cout << c << endl;
    }
}