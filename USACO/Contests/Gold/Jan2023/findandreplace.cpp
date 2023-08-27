// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll l, r, o;
vector<ll> sz;
vector<vector<int>> adj;

void dfs(int s, ll j) {
    //cout << s << endl;
    //cout << sz[s] << endl;
    for(int u : adj[s]) {
        if(j + sz[u] >= l && j < r)
            dfs(u, j);
        j += sz[u];
        if(j > r || j < 0) j = r + 1;
    }
    if(s < 26)
        cout << (char) (s + 'a');
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> l >> r >> o;
    vector<pair<char, string>> oper(o);
    for(int i = 0; i < o; i++)
        cin >> oper[i].first >> oper[i].second;
    vector<int> top(26);
    adj.resize(26 + o);
    sz.resize(26 + o);
    for(int i = 0; i < 26; i++) top[i] = i, sz[i] = 1;
    for(int i = o - 1; i >= 0; i--) {
        adj[26 + i].resize(oper[i].second.length());
        for(int j = 0; j < adj[26 + i].size(); j++)
            if(adj[top[oper[i].second[j] - 'a']].size() == 1)
                adj[26 + i][j] = adj[top[oper[i].second[j] - 'a']][0];
            else 
                adj[26 + i][j] = top[oper[i].second[j] - 'a'];
        for(int j = 0; j < adj[26 + i].size(); j++) {
            sz[26 + i] += sz[top[oper[i].second[j] - 'a']];
            if(sz[26 + i] > r || sz[26 + i] < 0) sz[26 + i] = r + 1;
        }
        top[oper[i].first - 'a'] = 26 + i;
    }
    dfs(top[0], 0);
    cout << endl;
}
