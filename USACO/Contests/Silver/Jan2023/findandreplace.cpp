#include <bits/stdc++.h>
using namespace std;
#define MAXC 52
int adj[MAXC];

void testcase()
{
    string a, b;
    cin >> a >> b;
    fill(adj, adj + MAXC, -1);

    for (int i = 0; i < a.length(); i++)
    {
        int ai = (a[i] >= 'a') ? (a[i] - 'a') : (a[i] - 'A' + 26);
        int bi = (b[i] >= 'a') ? (b[i] - 'a') : (b[i] - 'A' + 26);
        if (adj[ai] == -1 || adj[ai] == bi)
            adj[ai] = bi;
        else
        {
            cout << -1 << endl;
            return;
        }
    }

    int strokes = 0;
    for (int i = 0; i < MAXC; i++)
    {
        vector<bool> done(52);
        int x = i;
        done[x] = true;
        do
        {
            x = adj[x];
            if (x == -1)
                break;
            if (done[x])
                break;
            done[x] = true;
        } while (true);

        if (x == i && adj[i] != i)
        {
            int found = -1;
            for (int j = 0; j < MAXC; j++)
                if (adj[j] == adj[i] && j != i)
                    found = j;

            if (found == -1)
            {
                bool skip = false;
                for (int j = i + 1; j < MAXC; j++)
                    if (done[j])
                        skip = true;
                if (skip)
                    continue;
                for (int j = 0; j < MAXC; j++)
                    if (adj[j] == -1 && j != i)
                        found = j;
                if (found == -1)
                {
                    cout << -1 << endl;
                    return;
                }
                else
                    adj[found] = adj[i], adj[i] = -1, strokes++;
            }
            else
                adj[i] = -1, strokes++;
        }
    }
    for (int i = 0; i < MAXC; i++)
        strokes += adj[i] != i && adj[i] != -1;
    cout << strokes << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        testcase();
}