#include <bits/stdc++.h>
using namespace std;

int N;
vector<pair<int, int>> linkedlist;
vector<pair<int, int>> sorted;

int main()
{
    cin >> N;
    linkedlist.resize(N + 2);
    for (int i = 1; i <= N; i++)
    {
        int h;
        cin >> h;
        linkedlist[i + 1].first = i;
        linkedlist[i - 1].second = i;
        sorted.push_back({h, i});
    }
    sort(sorted.begin(), sorted.end());
    long long ans = 0;
    for (pair<int, int> p : sorted)
    {
        if (linkedlist[p.second].first)
            ans += abs(linkedlist[p.second].first - p.second) + 1;
        if (linkedlist[p.second].second)
            ans += abs(linkedlist[p.second].second - p.second) + 1;

        linkedlist[linkedlist[p.second].first].second = linkedlist[p.second].second;
        linkedlist[linkedlist[p.second].second].first = linkedlist[p.second].first;
    }
    cout << ans << endl;
}
