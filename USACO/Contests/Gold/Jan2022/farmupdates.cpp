#include <bits/stdc++.h>
using namespace std;

vector<bool> removed;
vector<pair<int, int>> edges;
vector<vector<int>> adj;
vector<int> ans;

struct Query {
    char t;
    int a, b;
};

void dfs(int s, int t) {
    ans[s] = max(ans[s], t);
    for(int u : adj[s])
        if(ans[u] == -1)
            dfs(u, t);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    adj.resize(N + 1);
    vector<Query> queries(Q);
    ans.resize(N + 1, Q);
    for(int q = 0; q < Q; q++) {
        cin >> queries[q].t;
        if(queries[q].t == 'A') {
            cin >> queries[q].a >> queries[q].b;
            edges.push_back({queries[q].a, queries[q].b});
            removed.push_back(false);
        }
        else if(queries[q].t == 'R'){
            cin >> queries[q].a;
            removed[queries[q].a - 1] = true;
        }
        else {
            cin >> queries[q].a;
            ans[queries[q].a] = -1;
        }
    }
    for(int i = 0; i < edges.size(); i++)
        if(!removed[i])
            adj[edges[i].first].push_back(edges[i].second), adj[edges[i].second].push_back(edges[i].first);
    for(int i = 1; i <= N; i++)
        if(ans[i] == Q)
            dfs(i, Q);
    for(int q = Q - 1; q >= 0; q--) {
        if(queries[q].t == 'R') {
            int i = queries[q].a - 1;
            adj[edges[i].first].push_back(edges[i].second), adj[edges[i].second].push_back(edges[i].first);
            if(ans[edges[i].first] >= 0)
                dfs(edges[i].first, q);
            else if(ans[edges[i].second] >= 0)
                dfs(edges[i].second, q);
        }
        else if(queries[q].t == 'D') {
            int i = queries[q].a;
            if(ans[i] == -1)
                dfs(i, q);
        }
    }
    for(int i = 1; i <= N; i++) {
        cout << ans[i] << endl;
    }
}