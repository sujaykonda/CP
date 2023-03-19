#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct BIT
{
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k)
    {
        ll s = 0;
        while (k >= 1)
            s += tree[k], k -= k & -k;
        return s;
    }
    void add(int k, ll x)
    {
        while (k < (int)tree.size())
            tree[k] += x, k += k & -k;
    }
};

int n, q;
int t = 0;
vector<int> st;
vector<int> en;
vector<int> adj[2000001];

void dfs(int s, int e)
{
    st[s] = t++;
    for (int u : adj[s])
        if (u != e)
            dfs(u, s);
    en[s] = t - 1;
}

int main()
{
    cin >> n >> q;
    st.resize(n + 1);
    en.resize(n + 1);
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    BIT bit(t);
    for (int i = 1; i <= n; i++)
        bit.add(st[i] + 1, v[i]);

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            ll s, x;
            cin >> s >> x;
            bit.add(st[s] + 1, x - v[s]);
            v[s] = x;
        }
        else
        {
            ll s;
            cin >> s;
            cout << bit.sum(en[s] + 1) - bit.sum(st[s]) << endl;
        }
    }
}