#include <cplib/general.h>
using namespace std;

int main() {
    int n, m; rd(n); rd(m);
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b, c; rd(a), rd(b), rd(c);
        a--, b--;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }

    vector<ll> dist(n, -1);
    priority_queue<pair<ll, int>> pq; 
    dist[0] = 0;
    for(auto [u, v] : adj[0]) pq.push({-v, u});
    vector<string> lines;
    while(!pq.empty()) {
        int s = pq.top().second; ll d = pq.top().first; 
        pq.pop();
        if(dist[s] != -1) continue;
        ll mx = 0;
        lines.pb("");
        for(int i = 0; i < n; i++) {
            mx = max(dist[i], mx);
            lines.back() += (dist[i] == -1) ? '0' : '1';
        }
        lines.back() += " " + to_string(-d-mx);
        dist[s] = -d;
        if(s == n - 1) break;
        for(auto [u, v] : adj[s]) pq.push({d-v, u});
    }
    if(dist[n - 1] == -1) {
        cout << "inf" << endl;
    } else {
        cout << dist[n - 1] << " " << lines.size() << endl;
        for(string line : lines) cout << line << endl;
    }
}  