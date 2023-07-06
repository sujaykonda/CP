#include <cplib/general.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
void dfs(int s, int t, vector<int>& open) {
    while(adj[s].size() > 0 && adj[s].back().second > t) {
        dfs(adj[s].back().first, adj[s].back().second, open); 
        adj[s].pop_back();
    }
    if(adj[s].size() > 0 && adj[s].back().second == t)
        adj[s].pop_back();
    if(adj[s].size() > 0) open.pb(s);
}

void testcase() {
    int n; rd(n);
    adj = vector<vector<pair<int, int>>>(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a), rd(b);
        adj[a].pb({b, i}), adj[b].pb({a, i});
    }
    int ans = 0;
    vector<int> open; open.pb(1);
    while(open.size() > 0) {
        vector<int> nopen;
        for(int s : open)
            dfs(s, -1, nopen);
        open = nopen;
        ans++;
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}