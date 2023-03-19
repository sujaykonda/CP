#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> Coord;

int N;
vector<Coord> coords;
int cows[2501];
int prefix[2501][2501];

bool y_comp(Coord u, Coord v)
{
    return u.second < v.second;
}
int psum(int x, int y, int x2, int y2)
{
    return prefix[x2 + 1][y2 + 1] - prefix[x2 + 1][y] - prefix[x][y2 + 1] + prefix[x][y];
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        coords.push_back(make_pair(x, y));
    }
    sort(coords.begin(), coords.end(), y_comp);
    for (int i = 0; i < N; i++)
    {
        coords[i].second = i;
    }
    sort(coords.begin(), coords.end());
    for (int i = 0; i < N; i++)
    {
        cows[i] = coords[i].second;
        prefix[i + 1][cows[i] + 1] = 1;
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
    long long a = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            int y = min(cows[i], cows[j]);
            int y2 = max(cows[i], cows[j]);
            a += psum(i, 0, j, y) * psum(i, y2, j, N - 1);
        }
    }
    cout << a << endl;
}