#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double

ll T, K;
ld P[1001][1001];
ld A[1001];
ld B[1001];
ld ab[1001];
ld bb[1001];

ld calc(ld E, ld a, ld b, ll x)
{
    return pow(a, x) * E + b * (pow(a, x) - 1) / (a - 1);
}

int main()
{
    cin >> T >> K;
    T--;
    P[0][0] = 1;
    for (int i = 1; i <= T; i++)
    {
        P[i][0] = P[i - 1][0] / 2.0;
        for (int j = 1; j <= i; j++)
            P[i][j] = (P[i - 1][j] + P[i - 1][j - 1]) / 2;
    }
    A[0] = P[T][0];
    for (int i = 1; i <= T; i++)
        A[i] = A[i - 1] + P[T][i];

    B[T] = T * P[T][T];
    for (int i = T - 1; i >= 0; i--)
        B[i] = B[i + 1] + i * P[T][i];

    ld E = 0;
    while (K != 0)
    {
        ll i = (ll)floor(E);
        ld a = A[i], b = B[i + 1];
        ll lo = 1, hi = 1e9;
        while (hi > lo)
        {
            ll mid = (hi + lo + 1) / 2;
            if (floor(calc(E, a, b, mid)) == i)
                lo = mid;
            else
                hi = mid - 1;
        }
        lo = min(lo, K);
        E = calc(E, a, b, lo);
        K -= lo;
    }
    cout << fixed << setprecision(20);
    cout << E + 1 << endl;
}