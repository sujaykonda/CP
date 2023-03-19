#include <bits/stdc++.h>
using namespace std;
int N, Q;
int p[100001][3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("bcount.in", "r", stdin);
    freopen("bcount.out", "w", stdout);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        int j;
        cin >> j;
        p[i][0] = p[i - 1][0];
        p[i][1] = p[i - 1][1];
        p[i][2] = p[i - 1][2];
        p[i][j - 1]++;
    }

    for (int q = 1; q <= Q; q++)
    {
        int a, b;
        cin >> a >> b;
        cout << p[b][0] - p[a - 1][0] << " " << p[b][1] - p[a - 1][1] << " " << p[b][2] - p[a - 1][2] << '\n';
    }
}