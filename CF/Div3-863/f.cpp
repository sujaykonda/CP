#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    adjlist adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int k = 0;
    for(int i = 0; i < n; i++) k += adj[i].size() == 4;
    if(n != k * k) {
        cout << "NO" << endl;
        return;
    }
    int nk = 0;
    for(int i = 0; i < n; i++) nk += adj[i].size() == 2;
    if(nk + k != n) {
        cout << "NO" << endl;
        return;
    }
    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 4) {
            int mcnt = 0, ocnt = 0;
            for(int u : adj[i]) {
                if(adj[u].size() == 2) ocnt++;
                else mcnt++;
            }
            if(ocnt != mcnt) {
                cout << "NO" << endl;
                return;
            }
        }
    }

    vector<bool> allowed(n);
    vector<bool> done(n);
    function<bool(int, int, int)> dfs = [&] (int s, int e, int h) {
        done[s] = true;
        bool good = true;
        if(s == h) {
            for(int u : adj[s]) {
                if(allowed[u]) {
                    good = dfs(u, s, h); 
                    break;
                }
            }
        } else {
            for(int u : adj[s]) {
                if(allowed[u]) {
                    if(done[u]) {
                        if(u != e && u != h) {
                            return false;
                        }
                    } else {
                        good = dfs(u, s, h);
                    }
                } else {
                    if(adj[s].size() == 2) {
                        return false;
                    }
                }
            }
        }
        return good;
    };
    int last = 0;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 4) allowed[i] = true, last = i; 
    }
    if(!dfs(last, -1, last)) {
        cout << "NO" << endl;
        return;
    }
    int dcnt = 0;
    for(int i = 0; i < n; i++) dcnt += done[i];
    if(dcnt != k) {
        cout << "NO" << endl;
        return;
    }
    fill(done.begin(), done.end(), false);
    for(int i = 0; i < n; i++) allowed[i] = !allowed[i];
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(!allowed[i]) {
            cnt++;
            allowed[i] = true;
            if(!dfs(i, -1, i)) {
                cout << "NO" << endl;
                return;
            }
            int dcnt = 0;
            for(int i = 0; i < n; i++) dcnt += done[i];
            if(dcnt != cnt * k) {
                cout << "NO" << endl;
                return;
            }
            allowed[i] = false;
        }
    }
    cout << "YES" << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}