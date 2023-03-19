#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxv 2000001
#define mina 1000000

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    vector<int> comp(maxv, -1);
    for (int i = 0; i < N; i++)
        comp[A[i] + mina] = i;

    vector<vector<int>> dp(N, vector<int>(N));
    vector<ll> cnt(N);
    for (int i = 1; i < N; i++)
    {
        dp[0][i] = dp[0][i - 1] + cnt[comp[A[i] + mina]];
        for (int j = 0; j < i; j++)
            if (A[i] + A[j] + mina < maxv && comp[A[i] + A[j] + mina] != -1)
                cnt[comp[A[i] + A[j] + mina]]++;
    }
    cout << dp[0][N - 1] << endl;
}