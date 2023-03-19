#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000001

int n;
int freq[MAXN];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        freq[x]++;
    }
    int best = 1;
    for (int i = 2; i < MAXN; i++)
    {
        int s = 0;
        for (int j = 0; j < MAXN && s < 2; j += i)
            s += freq[j];
        if (s >= 2)
            best = i;
    }
    cout << best << endl;
}