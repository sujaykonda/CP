#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<char>> dirs;
vector<vector<int>> cnt;
vector<vector<int>> cost;

int calc_cost()
{
    int c = 0;
    for (int i = 0; i < N; i++)
        c += cnt[N][i] * cost[N][i] + cnt[i][N] * cost[i][N];
    return c;
}

void recalc(int i, int j, int mod)
{
    cnt[i][j] += mod;
    if (i == N || j == N)
        return;
    if (dirs[i][j] == 'R')
        recalc(i, j + 1, mod);
    else
        recalc(i + 1, j, mod);
}

int main()
{
    cin >> N;
    dirs.resize(N, vector<char>(N));
    cost.resize(N + 1, vector<int>(N + 1));
    cnt.resize(N + 1, vector<int>(N + 1));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cin >> dirs[i][j];
        cin >> cost[i][N];
    }
    for (int i = 0; i < N; i++)
        cin >> cost[N][i];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cnt[i][j] = 1;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dirs[i][j] == 'R')
                cnt[i][j + 1] += cnt[i][j];
            else
                cnt[i + 1][j] += cnt[i][j];
        }
    }

    cout << calc_cost() << endl;
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int i, j;
        cin >> i >> j;
        i--, j--;
        dirs[i][j] = dirs[i][j] == 'R' ? 'D' : 'R';
        if (dirs[i][j] == 'R')
            recalc(i + 1, j, -cnt[i][j]), recalc(i, j + 1, cnt[i][j]);
        else
            recalc(i, j + 1, -cnt[i][j]), recalc(i + 1, j, cnt[i][j]);
        cout << calc_cost() << endl;
    }
}