#include <bits/stdc++.h>
using namespace std;

long long n;
long long counter[200002];
long long p[200002];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
        p[i] += p[i - 1];
        p[i] = (p[i] % n);
        if (p[i] < 0)
            p[i] += n;
    }

    long long c = 0;
    for (int i = 0; i <= n; i++)
    {
        c += counter[p[i]];
        counter[p[i]]++;
    }
    cout << c << endl;
}