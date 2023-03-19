#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll N, Q;
vector<tuple<ll, ll, ll>> updates;
vector<pair<ll, ll>> queries;
vector<ll> so;
vector<ll> cc;
ll d[400001];
ll p[400001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    for (int n = 1; n <= N; n++)
    {
        ll l, r, v;
        cin >> l >> r >> v;
        updates.push_back({l, r, v});
        so.push_back(l);
        so.push_back(r);
    }
    for (int q = 1; q <= Q; q++)
    {
        ll l, r;
        cin >> l >> r;
        queries.push_back({l, r});
        so.push_back(l);
        so.push_back(r);
    }
    sort(so.begin(), so.end());
    cc.push_back(so[0]);
    for (int i = 1; i < so.size(); i++)
        if (so[i] != so[i - 1])
            cc.push_back(so[i]);
    for (tuple<ll, ll, ll> u : updates)
    {
        int i = lower_bound(cc.begin(), cc.end(), get<0>(u)) - cc.begin();
        int j = lower_bound(cc.begin(), cc.end(), get<1>(u)) - cc.begin();
        d[i] += get<2>(u);
        d[j] -= get<2>(u);
    }
    ll c = 0;
    for (int i = 1; i < cc.size(); i++)
    {
        c += d[i - 1];
        p[i] = p[i - 1] + c * (cc[i] - cc[i - 1]);
    }
    for (pair<int, int> q : queries)
    {
        int i = lower_bound(cc.begin(), cc.end(), q.first) - cc.begin();
        int j = lower_bound(cc.begin(), cc.end(), q.second) - cc.begin();
        cout << p[j] - p[i] << endl;
    }
}
