#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100000

int N, K;

int adj[MAX_N + 1];
int ans[MAX_N + 1];
vector<int> visitedK[MAX_N + 1];
int main()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        adj[i] = i;
        visitedK[i].push_back(i);
    }

    for (int k = 0; k < K; k++)
    {
        int ai, bi;
        cin >> ai >> bi;
        visitedK[adj[ai]].push_back(bi);
        visitedK[adj[bi]].push_back(ai);
        swap(adj[ai], adj[bi]);
    }

    for (int i = 1; i <= N; i++)
    {
        if (ans[i] > 0)
            continue;
        int x = i, y = i;
        do
        {
            x = adj[x];
            y = adj[adj[y]];
        } while (x != y);
        set<int> visited;
        do
        {
            for (int p : visitedK[x])
                visited.insert(p);
            x = adj[x];
        } while (x != y);
        do
        {
            ans[x] = visited.size();
            x = adj[x];
        } while (x != y);
    }

    for (int i = 1; i <= N; i++)
        cout << ans[i] << endl;
}