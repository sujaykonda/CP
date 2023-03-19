#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, q;
string ln;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string ln;
    cin >> ln;
    cin >> q;
    for (int qi = 0; qi < q; qi++)
    {
        int m;
        char c;
        cin >> m >> c;
        int ma = 0;
        for (int i = 0, j = 0; i < n; i++)
        {
            while (j < n && (ln[j] == c || m > 0))
                m -= (ln[j] != c), j++;
            ma = max(ma, j - i);
            m += (ln[i] != c);
        }
        cout << ma << endl;
    }
}