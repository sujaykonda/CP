#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

int N, M;

vector<pair<int, int>> cows;

vector<int> adj[MAXN];
vector<pair<int, int>> tadj[MAXN];

vector<int> comps;

bitset<MAXN> done;
bitset<MAXN> done2;
bitset<MAXN> tree;

bitset<MAXN> got_cereal;

queue<int> a;

void dfs(int s)
{
    done[s] = 1;
    for (int c : adj[s])
    {
        comps.push_back(c);
        int u = cows[c].first == s ? cows[c].second : cows[c].first;
        if (!done[u])
        {
            tree[c] = 1;
            dfs(u);
        }
    }
}
int avoid;
void dfs2(int s)
{
    done2[s] = 1;
    for (int c : adj[s])
    {
        int u = cows[c].first == s ? cows[c].second : cows[c].first;
        if (!got_cereal[c] && !done2[u])
        {
            got_cereal[c] = 1;
            a.push(c);
            dfs2(u);
        }
    }
}

int main()
{
    cin >> N >> M;
    cows.resize(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> cows[i].first >> cows[i].second;
        adj[cows[i].first].push_back(i);
        adj[cows[i].second].push_back(i);
    }
    for (int i = 1; i <= M; i++)
    {
        if (!done[i])
        {
            dfs(i);
            if (comps.size() == 0)
                continue;
            int root = 0;
            for (int c : comps)
            {
                if (!tree[c])
                {
                    root = c;
                    break;
                }
            }
            if (root == 0)
            {
                dfs2(cows[comps[0]].first);
            }
            else
            {
                got_cereal[root] = 1;
                a.push(root);
                dfs2(cows[root].first);
            }
            comps.clear();
        }
    }
    int hungry = 0;
    for (int i = 1; i <= N; i++)
        if (!got_cereal[i])
            a.push(i), hungry++;
    cout << hungry << endl;
    while (!a.empty())
        cout << a.front() << endl, a.pop();
}