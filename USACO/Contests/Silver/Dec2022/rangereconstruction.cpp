#include <bits/stdc++.h>
using namespace std;

int N;
long long r[301][301];
long long mi[301][301];
long long ma[301][301];
vector<long long> a;

bool check(long long n, int i)
{
    for (int j = 0; j <= i; j++)
    {
        if (max(ma[j][i], n) - min(mi[j][i], n) != r[j][i + 1])
        {
            return false;
        }
    }
    return true;
}

bool recursion(int i)
{
    if (i == N - 1)
        return true;
    if (check(a[i] + r[i][i + 1], i))
    {
        a.push_back(a[i] + r[i][i + 1]);
        for (int j = 0; j <= i + 1; j++)
        {
            ma[j][i + 1] = max(ma[j][i], a[i + 1]);
            mi[j][i + 1] = min(mi[j][i], a[i + 1]);
        }
        if (recursion(i + 1))
            return true;
        a.pop_back();
    }
    if (check(a[i] - r[i][i + 1], i))
    {
        a.push_back(a[i] - r[i][i + 1]);
        for (int j = 0; j <= i + 1; j++)
        {
            ma[j][i + 1] = max(ma[j][i], a[i + 1]);
            mi[j][i + 1] = min(mi[j][i], a[i + 1]);
        }
        if (recursion(i + 1))
            return true;
        a.pop_back();
    }
    return false;
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            cin >> r[i][j];
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mi[i][j] = INT_MAX;
            ma[i][j] = INT_MIN;
        }
    }
    a.push_back(0);
    mi[0][0] = 0;
    ma[0][0] = 0;
    recursion(0);
    /*
    long long totalmin = a[0];
    for (int i = 1; i < N; i++)
        totalmin = min(totalmin, a[i]);
    for (int i = 0; i < N; i++)
        a[i] -= totalmin + 1000000000;*/
    cout << a[0];
    for (int i = 1; i < a.size(); i++)
    {
        cout << " " << a[i];
    }
    cout << endl;
}