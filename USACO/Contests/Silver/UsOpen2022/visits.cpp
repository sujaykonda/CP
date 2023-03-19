#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N;
vector<int> childs[100001];
int adj[100001];
long long v[100001];

bool done[100001];

void mark_done(int x)
{
    if (done[x])
        return;
    done[x] = true;
    for (int child : childs[x])
    {
        mark_done(child);
    }
}

int main()
{
    // freopen("2.in", "r", stdin);
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> adj[i] >> v[i];
        childs[adj[i]].push_back(i);
    }
    long long ans = 0;
    for (int i = 1; i <= N; i++)
    {
        ans += v[i];
    }

    for (int i = 1; i <= N; i++)
    {
        if (!done[i])
        {
            int x = i, y = i;
            do
            {
                x = adj[x];
                y = adj[adj[y]];
            } while (x != y);
            long long m = v[x];
            do
            {
                x = adj[x];
                m = min(m, v[x]);
            } while (x != y);
            mark_done(x);
            ans -= m;
        }
    }
    cout << ans << endl;
}