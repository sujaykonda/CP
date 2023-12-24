#include <cplib/general.h>
using namespace std;

int main() {
    int n, q; rd(n, q);
    adjlist adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<vector<int>> queries(n);
    vector<vector<int>> alist(q);
    for(int i = 0; i < q; i++) {
        int x, k; rd(x, k); x--;
        alist[i] = vector<int>(k); rd(alist[i]);
        for(int& a : alist[i]) a--;
        queries[x].push_back(i);
    }
    vector<ll> mx(4 * n);
    vector<ll> lz(4 * n);
    auto push = [&] (int s) {
        if(lz[s] != 0) {
            mx[2 * s] += lz[s];
            mx[2 * s + 1] += lz[s];
            lz[2 * s] += lz[s];
            lz[2 * s + 1] += lz[s];
            lz[s] = 0;
        }
    };

    function<void(int, int, int, int, int, int)> upd = [&] (int u, int l, int r, int s, int lb, int rb) {
        l = max(lb, l), r = min(rb, r);
        if(l > r) return;
        if(l == lb && rb == r) {
            lz[s] += u;
            mx[s] += u;
        } else {
            int m = (lb + rb) / 2;
            push(s);
            upd(u, l, r, 2 * s, lb, m);
            upd(u, l, r, 2 * s + 1, m + 1, rb);         
            mx[s] = max(mx[2 * s], mx[2 * s + 1]);   
        }
    };

    vector<int> o;
    vector<pair<int, int>> range(n);

    function<void(int, int, int)> dfs = [&] (int s, int e, int d) {
        range[s].first = o.size();
        upd(d, o.size(), o.size(), 1, 0, n - 1);
        o.pb(s);
        for(int u : adj[s]) {
            if(u != e) {
                dfs(u, s, d + 1);
            }
        }
        range[s].second = o.size() - 1;
    };

    dfs(0, -1, 0);

    vector<int> anc(n, -1);
    vector<int> ans(q);

    function<void(int)> dfs2 = [&] (int s) {
        if(s != 0) {
            upd(-2, range[s].first, range[s].second, 1, 0, n - 1);
            upd(1, 0, n - 1, 1, 0, n - 1);
        }
        for(int i : queries[s]) {
            for(int a : alist[i]) {
                if(anc[a] != -1) {
                    upd(1e9, range[anc[a]].first, range[anc[a]].second, 1, 0, n - 1);
                    upd(-1e9, 0, n - 1, 1, 0, n - 1);
                } else {
                    upd(-1e9, range[a].first, range[a].second, 1, 0, n - 1);
                }
            }
            ans[i] = mx[1];
            for(int a : alist[i]) {
                if(anc[a] != -1) {
                    upd(-1e9, range[anc[a]].first, range[anc[a]].second, 1, 0, n - 1);
                    upd(1e9, 0, n - 1, 1, 0, n - 1);
                } else {
                    upd(1e9, range[a].first, range[a].second, 1, 0, n - 1);
                }
            }
        }
        for(int u : adj[s]) {
            if(anc[u] == -1) {
                anc[s] = u;
                dfs2(u);
            }
        }
        anc[s] = -1;
        if(s != 0) {
            upd(2, range[s].first, range[s].second, 1, 0, n - 1);
            upd(-1, 0, n - 1, 1, 0, n - 1);
        }
    };

    dfs2(0);

    for(int i : ans) cout << i << endl;
}