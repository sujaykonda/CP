#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int Aw = 0, Ab = 0, Bw = 0, Bb = 0, d = 0;
        while (n > 0)
        {
            if (d % 4 < 2)
                Ab += min(n, d) / 2, Aw += (min(n, d) + 1) / 2;
            else
                Bw += min(n, d) / 2, Bb += (min(n, d) + 1) / 2;
            n -= d;
            d++;
        }
        cout << Aw << " " << Ab << " " << Bw << " " << Bb << endl;
    }
}