#include <bits/stdc++.h>
using namespace std;

int N;
int M;

vector<int> adj[100001];
int color[100001];
int comp[100001];

void dfs(int s, int e, int c, int id)
{
    if (color[s] != c)
        return;

    comp[s] = id;
    for (int u : adj[s])
    {
        if (u == e)
            continue;

        dfs(u, s, c, id);
    }
}

int main()
{
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");

    fin >> N >> M;
    string line;
    fin >> line;
    for (int i = 1; i <= N; i++)
        color[i] = line[i - 1] - 'G';

    for (int i = 0; i < N - 1; i++)
    {
        int X, Y;
        fin >> X >> Y;
        adj[X].push_back(Y);
        adj[Y].push_back(X);
    }

    int id = 1;
    for (int i = 1; i <= N; i++)
    {
        if (comp[i] == 0)
        {
            dfs(i, 0, color[i], id);
            id++;
        }
    }

    for (int i = 0; i < M; i++)
    {
        int A, B;
        char C;
        fin >> A >> B >> C;
        if (comp[A] != comp[B])
        {
            fout << '1';
        }
        else
        {
            if (color[A] == (C - 'G'))
                fout << '1';
            else
                fout << '0';
        }
    }
    fout << endl;
}