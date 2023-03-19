#include <bits/stdc++.h>
using namespace std;
int t;
long long P[100001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int ti = 0; ti < t; ti++)
    {
        int n;
        cin >> n;
        string ln;
        cin >> ln;

        for (int i = 0; i < n; i++)
        {
            long long a = ln[i] - '0';
            P[i + 1] = P[i] + a;
        }
        long long c = 0;
        unordered_map<long long, long long> counter;
        for (int i = 0; i <= n; i++)
        {
            c += counter[P[i] - i];
            counter[P[i] - i]++;
        }
        cout << c << '\n';
    }
}