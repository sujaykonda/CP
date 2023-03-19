#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> adj[501];
int dist[501][501];
int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        bool good = true;
        for (int j = 1; j <= N; j++)
        {
            int pi;
            cin >> pi;
            if (good)
                adj[i].push_back(pi);
            if (pi == i)
                good = false;
        }
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j : adj[i])
        {
            dist[i][j] = 1;
        }
    }

    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                dist[i][j] = max(dist[i][j], dist[i][k] & dist[k][j]);
            }
        }
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j : adj[i])
        {
            if (dist[j][i])
            {
                cout << j << endl;
                break;
            }
        }
    }
}