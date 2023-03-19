#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    char c;
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> c, grid[i][j] = c == 'X';

    vector<vector<int>> pref(N, vector<int>(M + 1));
    for (int i = 0; i < N; i++)
        for (int j = 1; j <= M; j++)
            pref[i][j] = pref[i][j - 1] + grid[i][j - 1];

    int area = 0;
    for (int s = 0; s < M; s++)
    {
        for (int e = s; e < M; e++)
        {
            int last = -1;
            for (int i = 0; i < N; i++)
            {
                if (grid[i][s] || grid[i][e])
                    last = -1;
                if (pref[i][e + 1] - pref[i][s] == 0)
                {
                    if (last == -1)
                        last = i;
                    area = max(area, (i - last + 1) * (e - s + 1));
                }
            }
        }
    }
    cout << area << endl;
}