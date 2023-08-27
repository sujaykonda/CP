#include <cplib/graph/flow.h>
using namespace std;

int main() {
    int n, m; rd(n, m);
    vector<string> access(n); rd(access);
    vector<vector<bool>> adj(m, vector<bool>(m, true));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < m; k++) {
                if(access[i][j] == '0' && access[i][k] == '1') {
                    adj[j][k] = false;
                }
            }
        }
    }
    vector<int> comp(m, -1);
    int cc = 0;
    for(int i = 0; i < m; i++) {
        if(comp[i] == -1) {
            for(int j = 0; j < m; j++) {
                if(adj[i][j] && adj[j][i]) {
                    comp[j] = cc;
                }
            }
            cc++;
        }
    }
    vector<vector<bool>> adjc(cc, vector<bool>(cc));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            adjc[comp[i]][comp[j]] = adjc[comp[i]][comp[j]] || adj[i][j];
        }
    }
    wadjlist flwadj(2 * cc + 2);
    for(int i = 0; i < cc; i++) {
        for(int j = 0; j < cc; j++) {
            if(i != j && adjc[i][j]) {
                flwadj[i].pb({j + cc, 1});
            }
        }
    }
    for(int i = 0; i < cc; i++) {
        flwadj[2 * cc].pb({i, 1});
        flwadj[i + cc].pb({2 * cc + 1, 1});
    }
    ffdfs(flwadj, 2 * cc, 2 * cc + 1);
    vector<int> p(cc, -1), rp(cc, -1);
    for(int i = 0; i < cc; i++) {
        for(auto [u, v] : flwadj[i]) {
            if(v == 1) {
                p[i] = u - cc;
                rp[u - cc] = i;
            }
        }
    }
    vector<vector<int>> groups;
    for(int i = 0; i < cc; i++) {
        if(rp[i] == -1) {
            int j = i;
            groups.pb({});
            while(j != -1) {
                for(int k = 0; k < m; k++) {
                    if(comp[k] == j)
                        groups.back().pb(k);
                }
                j = p[j];
            }
        }
    }
    vector<int> g(m), l(m);
    for(int i = 0; i < groups.size(); i++) {
        for(int j = 0; j < groups[i].size(); j++) {
            g[groups[i][j]] = i + 1;
            l[groups[i][j]] = j + 2;
        }
    }
    cout << groups.size() << endl;
    for(int i : g) cout << i << " ";
    cout << endl;
    for(int i : l) cout << i << " ";
    cout << endl;
    for(int i = 0; i < n; i++) {
        vector<int> ld(groups.size(), 1);
        for(int j = 0; j < m; j++) {
            if(access[i][j] == '1') {
                ld[g[j] - 1] = max(ld[g[j] - 1], l[j]);
            }
        }
        for(int ldi : ld) cout << ldi << " ";
        cout << endl;
    }
}