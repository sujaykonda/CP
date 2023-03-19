#include <bits/stdc++.h>
using namespace std;

int patches[251][251];
bool done[251][251];
int grid[251][251];
int N;
int color[62501];
int sizes[62501];
set<int> done2;
vector<int> adj[62501];

void floodfill1(int i, int j, int n, int id)
{
    if (i < 0 || i >= N || j < 0 || j >= N || grid[i][j] != n || patches[i][j] > 0)
        return;
    patches[i][j] = id;
    floodfill1(i + 1, j, n, id);
    floodfill1(i - 1, j, n, id);
    floodfill1(i, j + 1, n, id);
    floodfill1(i, j - 1, n, id);
}

void floodfill2(int i, int j, int id)
{
    if (i < 0 || i >= N || j < 0 || j >= N || done[i][j])
        return;
    if (patches[i][j] != id)
    {
        adj[id].push_back(patches[i][j]);
        adj[patches[i][j]].push_back(id);
        return;
    }
    done[i][j] = true;
    sizes[id]++;
    floodfill2(i + 1, j, id);
    floodfill2(i - 1, j, id);
    floodfill2(i, j + 1, id);
    floodfill2(i, j - 1, id);
}

int dfs(int id, int c, int c2)
{
    if ((color[id] != c && color[id] != c2) || done2.count(id))
        return 0;
    done2.insert(id);
    int m = sizes[id];
    for (int n : adj[id])
    {
        m += dfs(n, c, c2);
    }
    return m;
}

int main()
{
    ifstream fin("multimoo.in");
    ofstream fout("multimoo.out");

    fin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fin >> grid[i][j];
        }
    }

    int id = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (patches[i][j] == 0)
            {
                floodfill1(i, j, grid[i][j], id);
                color[id] = grid[i][j];
                id++;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!done[i][j])
            {
                floodfill2(i, j, patches[i][j]);
            }
        }
    }

    int maxsize = 0;
    int maxsize2 = 0;
    for (int i = 1; i < id; i++)
    {
        done2.clear();
        maxsize = max(maxsize, sizes[i]);
        for (int n : adj[i])
        {
            maxsize2 = max(maxsize2, dfs(n, color[i], color[n]));
        }
    }
    fout << maxsize << endl
         << maxsize2 << endl;
}
