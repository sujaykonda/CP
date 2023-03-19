#include <bits/stdc++.h>
using namespace std;

int n;
int x;
unordered_map<long long, long long> counter;
long long p[200001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
        p[i] += p[i - 1];
    }

    long long c = 0;
    for (int i = 0; i <= n; i++)
    {
        c += counter[p[i] - x];
        counter[p[i]]++;
    }
    cout << c << endl;
}