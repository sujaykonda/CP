#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> A;
vector<int> P;
vector<int> S;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    A.resize(N);
    P.resize(N);
    S.resize(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    P[0] = A[0];
    for (int i = 1; i < N; i++)
        P[i] = __gcd(P[i - 1], A[i]);
    S[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; i--)
        S[i] = __gcd(S[i + 1], A[i]);

    int m = 0;
    for (int i = 0; i < N - 2; i++)
        m = max(m, __gcd(P[i], S[i + 2]));

    m = max(m, S[1]);
    m = max(m, P[N - 2]);
    cout << m << endl;
}