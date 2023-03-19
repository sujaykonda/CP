#include <bits/stdc++.h>
using namespace std;

long long N, K, L;
vector<int> c;
int check(int i)
{
    if (c[i] < N - i)
    {
        long long maxdiff = 0;
        long long sumdiff = 0;
        for (int j = i; j < N; j++)
        {
            if (N - i > c[j])
            {
                maxdiff = max(maxdiff, N - i - c[j]);
                sumdiff += N - i - c[j];
            }
        }
        if (maxdiff > K || sumdiff > K * L)
            return false;
    }
    return true;
}
int main()
{
    cin >> N >> K >> L;
    c.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> c[i];
    }
    sort(c.begin(), c.end());
    int s = 0, e = N - 1, m;
    while (s <= e)
    {
        m = (s + e) / 2;
        if (check(m))
            e = m - 1;
        else
            s = m + 1;
    }
    cout << N - max(s, e) << endl;
}