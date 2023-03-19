#include <bits/stdc++.h>
using namespace std;

int N;
int B;

vector<int> snow;
vector<pair<int, int>> boots;

int res[251][251];

int floodfill(int p, int b)
{
    if (p == N - 1)
        return b;
    if (b == B)
        return INT_MAX;
    if (res[p][b] != -1)
        return res[p][b];

    res[p][b] = floodfill(p, b + 1);
    for (int p2 = p; p2 < N & p2 - p <= boots[b].second; p2++)
        if (boots[b].first >= snow[p] && boots[b].first >= snow[p2])
            res[p][b] = min(res[p][b], floodfill(p2, b));
    return res[p][b];
}
int main()
{
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");

    fin >> N >> B;
    snow.resize(N);
    boots.resize(B);

    for (int i = 0; i < N; i++)
        fin >> snow[i];
    for (int i = 0; i < B; i++)
        fin >> boots[i].first >> boots[i].second;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < B; j++)
            res[i][j] = -1;
    fout << floodfill(0, 0) << endl;
}