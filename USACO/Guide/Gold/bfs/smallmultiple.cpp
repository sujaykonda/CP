#include <bits/stdc++.h>
using namespace std;
#define inf 1000000
#define ll long long
int main()
{
    ll K;
    cin >> K;
    deque<int> q;
    vector<int> d(K, inf);
    d[1] = 1;
    q.push_front(1);
    while (!q.empty())
    {
        int x = q.front();
        q.pop_front();
        int c1 = x * 10 % K;
        if (d[c1] > d[x])
        {
            d[c1] = d[x];
            q.push_front(c1);
        }

        int c2 = (x + 1) % K;
        if (d[c2] > d[x] + 1)
        {
            d[c2] = d[x] + 1;
            q.push_back(c2);
        }
    }
    cout << d[0] << endl;
}