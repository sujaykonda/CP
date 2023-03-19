#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);
    ll N, M;
    cin >> N >> M;
    vector<ll> f(N), s(N);
    for (int i = 0; i < N; i++)
        cin >> f[i] >> s[i];
    ll mn = -1;
    ll fsum = 0;
    multiset<ll> sw;
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        while (j < N && fsum < M)
        {
            fsum += f[j];
            sw.insert(s[j]);
            j++;
        }
        if (fsum < M)
            break;
        if (mn == -1 || mn > *sw.rbegin())
            mn = *sw.rbegin();
        fsum -= f[i];
        sw.erase(sw.find(s[i]));
    }
    cout << mn << endl;
}