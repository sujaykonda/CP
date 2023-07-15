#include <cplib/general.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> col;
bool good;
void dfs(int s, int c) {
    col[s] = c;
    for(auto [u, v] : adj[s]) {
        if(col[u] == 0) {
            dfs(u, c * v);
        } else {
            good = good && (col[u] == c * v);
        }
    }
}

void tc() {
    int n, m, k; rd(n, m, k);
    adj = vector<vector<pair<int, int>>>(n + m - 1);
    col = vector<int>(n + m - 1);
    for(int i = 0; i < k; i++) {
        int x1, y1, x2, y2; rd(x1, y1, x2, y2);
        adj[x1].pb({min(y1, y2) + n - 1, (y1 > y2 ? 1 : -1)});
        adj[min(y1, y2) + n - 1].pb({x1, (y1 > y2 ? 1 : -1)});
    }
    good = true;
    for(int i = 1; i < n + m - 1; i++) if(col[i] == 0) dfs(i, 1);

    cout << ((good) ? "YES" : "NO") << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}