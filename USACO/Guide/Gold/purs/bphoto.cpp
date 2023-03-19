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

int main()
{
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);
    int N;
    cin >> N;
    vector<pair<int, int>> h(N);
    for (int i = 0; i < N; i++)
        cin >> h[i].first, h[i].second = i;
    sort(h.begin(), h.end());
    vector<int> ch(N);
    for (int i = 0; i < N; i++)
        ch[h[i].second] = N - i;
    BIT lbit(N);
    vector<int> l(N);
    for (int i = 0; i < N; i++)
    {
        l[i] = lbit.sum(ch[i] - 1);
        lbit.add(ch[i], 1);
    }
    BIT rbit(N);
    vector<int> r(N);
    for (int i = N - 1; i >= 0; i--)
    {
        r[i] = rbit.sum(ch[i] - 1);
        rbit.add(ch[i], 1);
    }
    int cnt = 0;
    for (int i = 0; i < N; i++)
        cnt += (max(l[i], r[i]) > 2 * min(l[i], r[i]));
    cout << cnt << endl;
}