#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<int> dsizes;
int dcount[50000];
pair<int, int> rmax[50000];

int main()
{
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        int d;
        cin >> d;
        dsizes.push_back(d);
    }
    sort(dsizes.begin(), dsizes.end());

    int i = 0;
    int j = 0;
    while (i < N)
    {
        if (j < N && dsizes[i] + K >= dsizes[j])
        {
            j++;
            continue;
        }
        dcount[i] = j - i;
        i++;
        while (dsizes[i - 1] == dsizes[i])
            i++;
    }
    rmax[0].first = dcount[0];
    rmax[N - 1].second = dcount[N - 1];
    for (int i = 1; i < N; i++)
    {
        rmax[i].first = max(dcount[i], rmax[i - 1].first);
        // cout << rmax[i].first << endl;
    }
    for (int i = N - 2; i >= 0; i--)
    {
        rmax[i].second = max(dcount[i], rmax[i + 1].second);
        // cout << rmax[i].second << endl;
    }

    i = 0;
    j = 0;
    int a = 0;
    while (j < N)
    {
        if (dsizes[i] + K >= dsizes[j])
        {
            j++;
            continue;
        }
        a = max(a, rmax[i].first + rmax[j].second);
        i++;
        while (dsizes[i - 1] == dsizes[i])
            i++;
    }
    cout << a << endl;
}