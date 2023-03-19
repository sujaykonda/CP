#include <bits/stdc++.h>
using namespace std;

int N, K, B;
int a[100001];
int P[100001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);

    cin >> N >> K >> B;
    for (int b = 1; b <= B; b++)
    {
        int i;
        cin >> i;
        a[i]++;
    }

    for (int i = 1; i <= N; i++)
        P[i] = P[i - 1] + a[i];

    int m = INT_MAX;
    for (int i = 1; i <= N - K; i++)
        m = min(m, P[i + K] - P[i]);
    cout << m << endl;
}