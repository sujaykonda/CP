#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> order;
vector<pair<int, int>> swaps[100000];
vector<int> un(100000);
vector<int> weights;
unordered_set<int> done;
unordered_set<int> cycle;
vector<int> cows;

void dfs(int s, int mw)
{
    cycle.insert(s);
    cows.push_back(order[s]);
    done.insert(s);
    for (int i = 0; i < swaps[s].size(); i++)
    {
        if (swaps[s][i].second >= mw && !done.count(swaps[s][i].first))
        {
            dfs(swaps[s][i].first, mw);
        }
    }
}

bool check(int w)
{
    cycle.clear();
    cows.clear();
    done.clear();
    int i = 0;
    for (int i = 0; i < N; i++)
    {
        if (!done.count(i))
        {
            dfs(i, w);
            for (int j = 0; j < cows.size(); j++)
            {
                if (!cycle.count(cows[j]))
                {
                    return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        int pi;
        cin >> pi;
        order.push_back(pi - 1);
    }

    for (int i = 0; i < M; i++)
    {
        int ai, bi, wi;
        cin >> ai >> bi >> wi;
        swaps[ai - 1].push_back(make_pair(bi - 1, wi));
        swaps[bi - 1].push_back(make_pair(ai - 1, wi));
        weights.push_back(wi);
    }
    bool neg1 = true;
    for (int i = 0; i < N; i++)
    {
        if (i != order[i])
        {
            neg1 = false;
            break;
        }
    }
    if (neg1)
    {
        cout << -1 << endl;
        return 0;
    }
    sort(weights.begin(), weights.end());

    int L = 0, R = weights.size(), mid = 0;
    while (L <= R)
    {
        mid = (L + R) / 2;
        if (check(weights[mid]))
            L = mid + 1;
        else
            R = mid - 1;
    }
    mid = (L + R) / 2;
    cout << weights[mid] << endl;
}