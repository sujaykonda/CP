#include <bits/stdc++.h>
using namespace std;
int mod2019[200001];
int P[200001];
long long counter[2019];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string ln;

    cin >> ln;
    int N = ln.size();
    mod2019[0] = 1;
    for (int i = 1; i < N; i++)
        mod2019[i] = (mod2019[i - 1] * 10) % 2019;
    P[0] = 0;
    for (int i = 1; i <= N; i++)
        P[i] = (((ln[i - 1] - '0') * mod2019[N - i]) + P[i - 1]) % 2019;

    long long c = 0;
    for (int i = 0; i <= N; i++)
    {
        c += counter[P[i]];
        counter[P[i]]++;
    }
    cout << c << endl;
}