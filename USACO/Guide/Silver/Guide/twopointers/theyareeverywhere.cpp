#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
set<char> types;
map<char, int> tcount;
bool check()
{
    for (char type : types)
        if (tcount[type] == 0)
            return false;
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string ln;
    cin >> ln;
    for (int i = 0; i < n; i++)
        types.insert(ln[i]);
    int mi = n;
    for (int i = 0, j = 0; i < n; i++)
    {
        while (j < n && !check())
            tcount[ln[j]]++, j++;
        if (!check())
            break;
        mi = min(mi, j - i);
        tcount[ln[i]]--;
    }
    cout << mi << endl;
}