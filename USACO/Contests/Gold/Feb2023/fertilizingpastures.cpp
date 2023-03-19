#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<int> d;
vector<ll> t;
vector<pair<ll, ll>> f;
vector<vector<int>> adj;
vector<ll> ens;
vector<int> p;
bool cmp(int a, int b) {
    return (f[a].first * (2 + t[b]) > f[b].first * (2 + t[a]));
}

void dfs0(int s) {
    for(int u : adj[s])
        dfs0(u);
    sort(adj[s].begin(), adj[s].end(), cmp);
    for(int u : adj[s]) {
        f[s].first += f[u].first;
        f[s].second += f[u].first * (t[s] + 1) + f[u].second;
        t[s] += 2 + t[u];
    }
}

void dfs1(int s, int e) {
    d[s] = d[e] + 1;
    ll csum = 0;
    for(int u : adj[s])
        csum += f[u].first;
    ll tsum = 0;
    for(int u : adj[s]) {
        csum -= f[u].first;
        ens[u] += ens[s] + f[u].first * (t[s] - t[u] - 2 - tsum) + csum * (- t[u] - 2);
        tsum += 2 + t[u];
    }
    for(int u : adj[s])
        dfs1(u, s);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int N, T;
    cin >> N >> T;
    adj.resize(N + 1);
    f.resize(N + 1);
    t.resize(N + 1);
    d.resize(N + 1);
    p.resize(N + 1);
    ens.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        int a;
        cin >> p[i] >> a;
        adj[p[i]].push_back(i);
        f[i].first = a;
    }
    dfs0(1);
    if(T == 0) {
        cout << t[1] << " " << f[1].second << endl;
    } else {
        dfs1(1, 0);
        int md = 0;
        for(int i = 1; i <= N; i++)
            md = max(d[i], md);
        int cnt = 0;
        ll mn = LONG_LONG_MAX;
        for(int i = 1; i <= N; i++) {
            if(d[i] == md) {
                mn = min(mn, f[1].second + ens[i]);
            }
        }
        cout << 2 * (N - 1) - md + 1 << " " << mn << endl;
    }
}