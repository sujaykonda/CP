#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int A = 0, B = 0, d = 0;
        while (n > 0)
        {
            if (d % 4 < 2)
                A += min(n, d);
            else
                B += min(n, d);
            n -= d;
            d++;
        }
        cout << A << " " << B << endl;
    }
}