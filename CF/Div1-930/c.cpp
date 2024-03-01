#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    vector<int> c(n); rd(c);
    vector<vector<int>> a(n, vector<int>(m)); rd(a);
    vector<vector<pair<int, int>>> adj(n * (m + 1));
    for(int i = 0; i < m; i++) {
        vector<int> o(n);
        for(int j = 0; j < n; j++) o[j] = j;
        sort(o.begin(), o.end(), [&] (int x, int y) { return a[x][i] < a[y][i]; });
        for(int j = 0; j < n - 1; j++) {
            int x = (m + 1) * o[j] + i, y = (m + 1) * o[j + 1] + i;
            adj[y].push_back({x, a[o[j + 1]][i] - a[o[j]][i]});
            adj[x].push_back({y, 0});
        }
        for(int j = 0; j < n; j++) {
            int x = (m + 1) * o[j] + i, y = (m + 1) * o[j] + m;
            adj[x].push_back({y, c[o[j]]});
            adj[y].push_back({x, 0});
        }
    }
    priority_queue<pair<ll, int>> pq;
    vector<bool> done(n * (m + 1));
    pq.push({0, m});
    while(pq.size() > 0) {
        auto [d, s] = pq.top();
        pq.pop();
        if(done[s]) continue;
        if(s == (m + 1) * (n - 1) + m) {
            cout << -d << endl;
        }
        done[s] = true;
        for(auto [u, v] : adj[s]) {
            if(!done[u]) {
                pq.push({d - v, u});
            }
        }
    }

}

int main() {
    int t; rd(t);
    while(t--) tc();
}