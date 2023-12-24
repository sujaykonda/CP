#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct D
{
    ll mnd, v, lz, c, sm;
    int lb, rb;
};
const ll INF = 1e18 + 1;

void solve()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> t(n);
    for (int i = 0; i < n; i++)
        cin >> t[i];
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    vector<D> data(2 * n);
    auto pull = [&](int s)
    {
        pair<ll, ll> mx = max(make_pair(data[2 * s].v, data[2 * s].c), make_pair(data[2 * s + 1].v, data[2 * s + 1].c));
        data[s].v = mx.first;
        data[s].c = mx.second;
        data[s].mnd = min(data[2 * s].mnd, data[2 * s + 1].mnd);
        if (data[s].c == 0)
        {
            if (data[2 * s].c == 1)
            {
                data[s].mnd = min(data[s].mnd, data[2 * s + 1].v - data[2 * s].v);
            }
            else if (data[2 * s + 1].c == 1)
            {
                data[s].mnd = min(data[s].mnd, data[2 * s].v - data[2 * s + 1].v);
            }
        }
        data[s].sm = data[s].c + data[2 * s].sm + data[2 * s + 1].sm;
        data[s].lb = data[2 * s].lb;
        data[s].rb = data[2 * s + 1].rb;
    };
    function<void(int)> push = [&](int s)
    {
        if (data[s].lz > 0)
        {
            if(data[2 * s].lb != data[2 * s].rb) {
                data[2 * s].mnd -= data[s].lz;
            }
            if(data[2 * s + 1].lb != data[2 * s + 1].rb) {
                data[2 * s + 1].mnd -= data[s].lz;
            }
            if (data[2 * s].c == 1)
                data[2 * s].v += data[s].lz;
            if (data[2 * s + 1].c == 1)
                data[2 * s + 1].v += data[s].lz;
            data[2 * s].lz += data[s].lz;
            data[2 * s + 1].lz += data[s].lz;
            data[s].lz = 0;
            
            if(data[2 * s].mnd <= 0) {
                push(2 * s); 
                pull(2 * s);
            }
            if(data[2 * s + 1].mnd <= 0) {
                push(2 * s + 1);
                pull(2 * s + 1);
            }
        }
    };
    function<void(int, int)> search = [&] (int s, int k) {
        if(data[s].lb == data[s].rb) {
            return;
        }
        push(s);
        if(data[2 * s].mnd == k) {
            search(2 * s, k);
        } else {
            search(2 * s + 1, k);
        }
        pull(s);
    };
    function<void(int, int, int, int)> upd = [&](int s, int l, int r, int k)
    {
        l = max(data[s].lb, l);
        r = min(data[s].rb, r);
        if (l > r)
            return;
        if (data[s].lb == l && data[s].rb == r)
        {
            data[s].lz += k;
            if (data[s].c == 1)
                data[s].v += k;
            if(l != r)
            {
                data[s].mnd -= k;
                if(data[s].mnd <= 0) {
                    push(s);
                    pull(s);
                }
            }
        }
        else
        {
            push(s);
            upd(2 * s, l, r, k);
            upd(2 * s + 1, l, r, k);
            pull(s);
        }
    };
    for (int i = 0; i < n; i++)
    {
        data[n + i].v = p[i];
        data[n + i].c = t[i];
        data[n + i].lb = i;
        data[n + i].rb = i;
        data[n + i].sm = 0;
        data[n + i].lz = 0;
        data[n + i].mnd = INF;
    }
    for (int i = n - 1; i >= 1; i--)
    {
        pull(i);
    }
    for (int i = 0; i < q; i++)
    {
        int l, r, b;
        cin >> l >> r >> b;
        l--, r--;
        upd(1, l, r, b);
        cout << data[1].sm << endl;
    }
}

int main()
{
    solve();
}
