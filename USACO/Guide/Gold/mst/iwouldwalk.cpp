#include <bits/stdc++.h>
using namespace std;

int calc(long long x, long long y)
{
    return (2019201913ll * x + 2019201949ll * y) % 2019201997ll;
}

int main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    int N, K;
    cin >> N >> K;

    vector<int> dist(N, 2019201997);
    vector<bool> done(N);
    for (int i = 0; i < N; i++)
    {
        int mn = -1;
        for (int j = 0; j < N; j++)
            if (!done[j] && (mn == -1 || dist[mn] > dist[j]))
                mn = j;
        done[mn] = true;
        for (int j = 0; j < N; j++)
            if (!done[j])
                dist[j] = min(dist[j], calc(min(mn, j) + 1, max(mn, j) + 1));
    }
    // now dist has all the distances of each vertex
    sort(dist.begin(), dist.end());
    cout << dist[N - K] << endl;
}