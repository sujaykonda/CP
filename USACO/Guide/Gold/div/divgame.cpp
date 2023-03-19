#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll N;
map<ll, ll> pf;
int main()
{
    cin >> N;
    if (N == 1)
    {
        cout << "0" << endl;
        return 0;
    }
    bool prime = false;
    while (!prime)
    {
        prime = true;
        for (int i = 2; i <= sqrt(N); i++)
        {
            if (N % i == 0)
            {
                pf[i]++;
                N /= i;
                prime = false;
                break;
            }
        }
    }
    pf[N]++;
    int c = 0;
    for (auto const &[key, val] : pf)
    {
        int np = val;
        for (int i = 1; np >= 0; i++)
            np -= i, c++;
        c--;
    }
    cout << c << endl;
}