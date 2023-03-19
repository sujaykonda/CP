#include <bits/stdc++.h>
using namespace std;

int N;
int p[100001][3];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        char c;
        cin >> c;
        p[i][0] = p[i - 1][0];
        p[i][1] = p[i - 1][1];
        p[i][2] = p[i - 1][2];
        p[i][((c == 'H') ? 0 : ((c == 'S') ? 1 : 2))]++;
    }
    int wins = 0;
    for (int i = 0; i <= N; i++)
    {
        wins = max(wins, max(p[i][0], max(p[i][1], p[i][2])) + max(p[N][0] - p[i][0], max(p[N][1] - p[i][1], p[N][2] - p[i][2])));
    }
    cout << wins << endl;
}