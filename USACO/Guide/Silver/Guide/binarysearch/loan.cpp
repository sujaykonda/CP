#include <bits/stdc++.h>
using namespace std;

#define HIGH 1000000000000

long long N, K, M;

bool check(long long X)
{
    long long k = 0;
    long long n = N;
    while (n / X > M && k < K)
    {
        long long dn = n / X;
        long long dk = (n % X) / dn + 1;
        n -= dk * dn;
        // cout << dk << " " << dn << " " << n / X << endl;
        k += dk;
    }
    return k + n / M + 1 <= K;
}

int main()
{
    ifstream fin("loan.in");
    ofstream fout("loan.out");

    fin >> N >> K >> M;

    long long L = 2, R = N - 1, mid = 0;
    while (L <= R)
    {
        mid = (L + R) / 2;
        if (check(mid))
            L = mid + 1;
        else
            R = mid - 1;
    }
    mid = (L + R) / 2;
    fout << mid << endl;
}