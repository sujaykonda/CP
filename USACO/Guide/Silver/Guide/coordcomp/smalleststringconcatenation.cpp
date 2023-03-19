#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<string> a;

bool cmp(string s1, string s2)
{
    return s1 + s2 < s2 + s1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), cmp);
    string c = "";
    for (string ai : a)
        c += ai;
    cout << c << endl;
}