#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<ll> len;
vector<vector<int>> adj;
vector<ll> totaldp;
vector<ll> subfiles;

int dfs(int s, int e) {
    cout << s << endl;
    cout << adj[s].size() << endl;
    ll sum = 0;
    for(int u : adj[s]) {
        if(u != e) {
            cout << u << endl;
            sum += dfs(u, s);
            sum += subfiles[u] * len[u];
            subfiles[s] += subfiles[u];
        }
    }
    return sum;
}

void dfs2(int s, int e) {
    if(s != e) totaldp[s] = totaldp[e] - len[s] * subfiles[s] + 3 * (subfiles[1] - subfiles[s]);
    for(int u : adj[s])
        if(u != e)
            dfs2(u, s);
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);
    int N;
    cin >> N;
    len.resize(N + 1);
    adj.resize(N + 1);
    subfiles.resize(N + 1);
    totaldp.resize(N + 1);
    for(int i = 1; i <= N; i++) {
        int m;
        cin >> noskipws;
        char c;
        while (cin >> c)
        {
            if(c == ' ')
                break;
            len[i]++;
        }
        cin >> skipws;
        cin >> m;
        subfiles[i] = m == 0;
        len[i] -= m == 0;
        for(int j = 0; j < m; j++) {
            int b;
            cin >> b;
            adj[i].push_back(b);
            adj[b].push_back(i);
        }
    }
    cout << "done input" << endl;
    totaldp[1] = dfs(1, 1); 
    cout << "done dfs 1" << endl;
    dfs2(1, 1);
    cout << "done dfs 2" << endl;
    ll mn = totaldp[1];
    for(int i = 1; i <= N; i++) mn = min(mn, totaldp[i]);
    cout << mn << endl;
}