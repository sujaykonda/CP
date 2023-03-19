#include <bits/stdc++.h>
using namespace std;
#define pi pair<long long, long long>

int N;
pi t;
vector<pi> points;

pi add(pi a, pi b)
{
    return {a.first + b.first, a.second + b.second};
}
pi sub(pi a, pi b)
{
    return {a.first - b.first, a.second - b.second};
}

vector<pair<pi, int>> subsets(int s, int e)
{
    vector<pair<pi, int>> v;
    v.push_back({{0, 0}, 0});
    for (int i = s; i < e; i++)
    {
        v.resize(2 * v.size());
        for (int j = 0; j < v.size() / 2; j++)
            v[v.size() / 2 + j] = {add(v[j].first, points[i]), v[j].second + 1};
    }
    return v;
}
struct hsh
{
    size_t operator()(const pi &p) const
    {
        return p.first * 134 + p.second;
    }
};

int main()
{
    cin >> N;

    points.resize(N);

    cin >> t.first >> t.second;
    for (int i = 0; i < N; i++)
        cin >> points[i].first >> points[i].second;

    vector<pair<pi, int>> fh = subsets(0, N / 2);
    vector<pair<pi, int>> lh = subsets(N / 2, N);
    unordered_map<pi, map<int, int>, hsh> fhc;
    for (pair<pi, int> p : fh)
        fhc[p.first][p.second]++;
    vector<long long> ans(N + 1);
    for (pair<pi, int> p : lh)
    {
        auto it = fhc.find(sub(t, p.first));
        if (it != fhc.end())
            for (pair<int, int> c : it->second)
                ans[p.second + c.first] += c.second;
    }
    for (int i = 1; i <= N; i++)
    {
        cout << ans[i] << "\n";
    }
}