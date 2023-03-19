#include <bits/stdc++.h>
using namespace std;

struct Event
{
    int q, u, v, n;
};

int N;
vector<Event> events;

bool cmp(Event e, Event o)
{
    return e.u == o.u ? e.q < o.q : e.u < o.u;
}

int main()
{
    cin >> N;
    events.resize(N);
    for (int i = 0; i < N; i++)
    {
        int x, t;
        cin >> events[i].q >> t >> x >> events[i].n;
        events[i].u = t - x, events[i].v = t + x;
    }
    sort(events.begin(), events.end(), cmp);
    int a = 0;
    multiset<pair<int, int>, greater<pair<int, int>>> vs;
    for (Event e : events)
    {
        if (e.q == 1)
            vs.insert({e.v, e.n});
        else
        {
            while (e.n > 0 && vs.size() > 0)
            {
                auto it = vs.lower_bound({e.v, 1001});
                if (it == vs.end())
                    break;
                int v = (*it).first, n = (*it).second;
                vs.erase(it);
                if (n > e.n)
                    n -= e.n, a += e.n, e.n = 0, vs.insert({v, n});
                else
                    e.n -= n, a += n;
            }
        }
    }
    cout << a << endl;
}