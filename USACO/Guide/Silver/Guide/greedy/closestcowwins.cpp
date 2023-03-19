#include <bits/stdc++.h>
using namespace std;

int K, M, N;
vector<pair<int, long long>> patches;
vector<int> ops;
vector<pair<pair<int, int>, long long>> intervals;
vector<pair<long long, pair<int, int>>> combintervals;

int main()
{
    cin >> K >> M >> N;

    for (int i = 0; i < K; i++)
    {
        pair<int, int> p;
        cin >> p.first >> p.second;
        patches.push_back(p);
    }
    for (int i = 0; i < M; i++)
    {
        int op;
        cin >> op;
        ops.push_back(op);
    }
    sort(patches.begin(), patches.end());
    sort(ops.begin(), ops.end());
    int i = 0;
    int j = 0;
    // generates intervals
    while (i < patches.size())
    {
        if (j < ops.size() - 1 && abs(patches[i].first - ops[j]) >= abs(patches[i].first - ops[j + 1]))
        {
            j++;
            continue;
        }
        int dist = abs(patches[i].first - ops[j]);
        pair<pair<int, int>, long long> interval = make_pair(make_pair(patches[i].first - dist, patches[i].first + dist), patches[i].second);
        intervals.push_back(interval);
        i++;
    }

    // combines intervals
    pair<long long, pair<int, int>> combinter = make_pair(intervals[0].second, intervals[0].first);
    for (int i = 1; i < intervals.size(); i++)
    {
        pair<long long, pair<int, int>> newinter = make_pair(combinter.first + intervals[i].second, make_pair(max(combinter.second.first, intervals[i].first.first),
                                                                                                              min(combinter.second.second, intervals[i].first.second)));
        if (newinter.second.first >= newinter.second.second)
        {
            combintervals.push_back(combinter);
            combinter = make_pair(intervals[i].second, intervals[i].first);
        }
        else
        {
            combinter = newinter;
        }
    }
    combintervals.push_back(combinter);
    sort(combintervals.begin(), combintervals.end());
    long long s = 0;
    for (int i = 1; i <= N; i++)
    {
        if (i > combintervals.size())
        {
            break;
        }
        s += combintervals[combintervals.size() - i].first;
    }
    cout << s << endl;
}