#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<pair<int, int>> cows;
priority_queue<int> waitlist;
priority_queue<pair<int, int>> events;
int main()
{
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        pair<int, int> ci;
        cin >> ci.first >> ci.second;
        cows.push_back(ci);
        events.push(make_pair(-ci.first, i));
    }
    int waiting = 0;
    int feeding = -1;
    while (events.size() > 0)
    {
        int t = -events.top().first;
        int i = events.top().second;
        // cout << t << " " << i << endl;
        if (feeding == i)
        {
            // cout << feeding << " has left at time: " << t << endl;
            feeding = -1;
        }
        else
        {
            waitlist.push(N - 1 - i);
        }
        if (feeding == -1 && waitlist.size() > 0)
        {
            feeding = N - 1 - waitlist.top();
            // cout << feeding << " has left the waitlist and stayed for " << t - cows[feeding].first << endl;
            waiting = max(waiting, (t - cows[feeding].first));
            waitlist.pop();
            events.push(make_pair(-(t + cows[feeding].second), feeding));
            // cout << feeding << " has started at time: " << t << endl;
        }
        events.pop();
    }
    cout << waiting << endl;
}