#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> adj;

struct D {
    vector<int> t, v;
};

vector<D> subdp, outdp;
vector<int> mndep, outmndep;

D shift(D a, int s) {
    D b; 
    for(int i = 0; i < a.t.size(); i++) {
        int t = max(0, a.t[i] + s);
        if(b.t.size() > 0 && b.t.back() == t) {
            b.v.back() = a.v[i];
        } else {
            b.t.push_back(t);
            b.v.push_back(a.v[i]);
        }
    }
    return b;
}
D lim(D a, int l) {
    while(a.t.size() > 0 && a.t.back() >= l) a.t.pop_back(), a.v.pop_back();
    return a;
}

D merge(D a, D b) {
    D c; c.t.resize(a.t.size() + b.t.size());
    c.t.resize(set_union(a.t.begin(), a.t.end(), b.t.begin(), b.t.end(), c.t.begin()) - c.t.begin());
    int ap = 0, bp = 0;
    for(int t : c.t) {
        while(ap + 1 < a.t.size() && a.t[ap + 1] <= t) ap++;
        while(bp + 1 < b.t.size() && b.t[bp + 1] <= t) bp++;
        c.v.push_back(a.v[ap] + b.v[bp]);
    }
    return c;
}

void print(D a) {
    for(int j = 0; j < a.t.size(); j++) {
        cout << "{" << a.t[j] << ", " << a.v[j] << "} ";
    }
    cout << endl;
}

void dfs(int s, int e) {
    if(adj[s].size() == 1) {
        subdp[s].t = {0};
        subdp[s].v = {1};
        mndep[s] = 0;
        return;
    }
    for(int u : adj[s]) {
        if(u != e) {
            dfs(u, s);
            mndep[s] = min(mndep[s], mndep[u] + 1);
        }
    }
    for(int u : adj[s]) {
        if(u != e) {
            subdp[s] = merge(subdp[s], lim(shift(subdp[u], -1), mndep[s]));
        }
    }
    if(subdp[s].v.empty() || subdp[s].v.back() > 1) {
        subdp[s].t.push_back(mndep[s]);
        subdp[s].v.push_back(1);
    }
}

void dfs2(int s, int e) {
    if(adj[s].size() == 1) return;
    vector<D> suffdp{outdp[s]};
    vector<int> suffmn{outmndep[s]};
    for(int u : adj[s]) {
        if(u != e) {
            suffdp.push_back(merge(suffdp.back(), shift(subdp[u], -1)));
            suffmn.push_back(min(suffmn.back(), mndep[u] + 1));
        }
    }
    suffdp.pop_back(), suffmn.pop_back();
    reverse(adj[s].begin(), adj[s].end());
    int mn = N;
    D dp{{0}, {0}};
    for(int u : adj[s]) {
        if(u != e) {
            outmndep[u] = min(mn, suffmn.back());
            outdp[u] = lim(merge(dp, suffdp.back()), outmndep[u]);
            if(outdp[u].v.empty() || outdp[u].v.back() > 1) {
                outdp[u].t.push_back(outmndep[u]);
                outdp[u].v.push_back(1);
            }
            outdp[u] = shift(outdp[u], -1);
            outmndep[u]++;
            suffdp.pop_back(), suffmn.pop_back();
            dp = merge(dp, shift(subdp[u], -1));
            mn = min(mn, mndep[u] + 1);
        }
    }
    for(int u : adj[s]) {
        if(u != e) {
            dfs2(u, s);
        }
    }
}



int main() {
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    adj.resize(N);
    for(int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if(N == 2) {
        cout << "1\n1\n";
        return 0;
    }
    int rt = 0;
    for(int i = 0; i < N; i++) 
        if(adj[i].size() > 1) {
            rt = i;
            break;
        }
    subdp.resize(N, D{{0}, {0}});
    mndep.resize(N, N);
    dfs(rt, -1);
    outdp.resize(N, D{{0}, {0}});
    outmndep.resize(N, N);
    dfs2(rt, -1);
    for(int i = 0; i < N; i++) {
        if(adj[i].size() == 1) {
            cout << 1 << endl;
        } else {
            cout << subdp[i].v[0] + outdp[i].v[0] << '\n';
        }
    }
}