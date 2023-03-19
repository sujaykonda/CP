#include <bits/stdc++.h>
using namespace std;

int t;

int main()
{
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        map<pair<int, int>, int> ratiocount;
        string ln;
        cin >> ln;
        int dc = 0, kc = 0;
        for (int i = 0; i < n; i++)
        {
            if (ln[i] == 'D')
                dc++;
            else
                kc++;
            pair<int, int> ratio = {dc, kc};
            if (dc == 0)
                ratio.second = 1;
            else if (kc == 0)
                ratio.first = 1;
            else
                ratio.first /= __gcd(dc, kc), ratio.second /= __gcd(dc, kc);
            ratiocount[ratio]++;
            cout << ratiocount[ratio] << endl;
        }
    }
}