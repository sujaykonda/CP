#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/general.h>
using namespace std;

int main() {
    int n, m; rd(n, m);
    adjlist adj(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> p(n + 1), sz(n + 1), dep(n + 1, -1);
    function<void(int, int)> dfs = [&] (int s, int e) {
        sz[s] = 1;
        for(int u : adj[s]) {
            if(u != e) {
                p[u] = s;
                dep[u] = dep[s] + 1;
                dfs(u, s);
                sz[s] += sz[u];
            }
        }
    };
    dep[1] = 0;
    dfs(1, 0);

    vector<int> pl(n + 1);
    vector<vector<int>> chains(n + 1);
    function<void(int, int)> dfs2 = [&] (int s, int e) {
        chains[pl[s]].pb(s);
        for(int u : adj[s]) {
            if(u != e) {
                if((sz[s] - 1) / 2 < sz[u]) {
                    pl[u] = pl[s];
                } else {
                    pl[u] = u;
                }
                dfs2(u, s);
            }
        }
    };
    pl[1] = 1;
    dfs2(1, 0);

    vector<int> o, ro(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int u : chains[i]) {
            ro[u] = o.size();
            o.pb(u);
        }
    }

    adjlist nadj(7 * n);

    function<void(int, int, int)> build = [&] (int s, int lb, int rb) {
        if(lb == rb) return;
        int m = (lb + rb) / 2;
        if(lb == m) {
            nadj[lb].pb(s + n);
            nadj[s + 4 * n].pb(lb);
        } else {
            nadj[2 * s + n].pb(s + n);
            nadj[s + 4 * n].pb(2 * s + 4 * n);
        }
        if(m + 1 == rb) {
            nadj[rb].pb(s + n);
            nadj[s + 4 * n].pb(rb);
        } else {
            nadj[2 * s + 1 + n].pb(s + n);
            nadj[s + 4 * n].pb(2 * s + 1 + 4 * n);
        }
        build(2 * s, lb, m);
        build(2 * s + 1, m + 1, rb);
    };
    function<void(int, bool, int, int, int, int, int)> upd = [&] (int u, bool mx, int l, int r, int s, int lb, int rb) {
        l = max(lb, l), r = min(rb, r);
        if(l > r) return;
        if(l == lb && r == rb) {
            if(mx) {
                if(lb == rb) {
                    nadj[lb].pb(u);
                } else {
                    nadj[s + n].pb(u);
                }
            } else {
                if(lb == rb) {
                    nadj[u].pb(lb);
                } else {
                    nadj[u].pb(s + 4 * n);
                }
            }
        } else {
            int m = (lb + rb) / 2;
            upd(u, mx, l, r, 2 * s, lb, m);
            upd(u, mx, l, r, 2 * s + 1, m + 1, rb);
        }
    };
    build(1, 0, n - 1);
    vector<vector<int>> jmp(lg(n + 1) + 1, vector<int>(n + 1));
    jmp[0] = p;
    for(int i = 0; i < jmp.size() - 1; i++)
        for(int j = 0; j <= n; j++)
            jmp[i + 1][j] = jmp[i][jmp[i][j]]; 
    
    auto q = [&] (int a, int b) {
        if(dep[a] < dep[b]) std::swap(a, b);
        for(int i = jmp.size() - 1; i >= 0; i--)
            if(dep[jmp[i][a]] >= dep[b]) 
                a = jmp[i][a];
        if(a == b) return a;
        for(int i = jmp.size() - 1; i >= 0; i--)
            if(jmp[i][a] != jmp[i][b]) 
                a = jmp[i][a], b = jmp[i][b];
        return jmp[0][a];
    };

    auto apply = [&] (int a, int b, int c, bool mx) {
        while(dep[a] >= dep[b]) {
            int e = pl[a];
            if(dep[e] < dep[b]) {
                e = b;
            }

            if(ro[e] <= ro[c] && ro[c] <= ro[a]) {
                //cout << o[ro[c] + 1] << " " << a << " " << c << endl;
                //cout << e << " " << o[ro[c] - 1] << " " << c << endl;
                upd(ro[c], mx, ro[c] + 1, ro[a], 1, 0, n - 1);
                upd(ro[c], mx, ro[e], ro[c] - 1, 1, 0, n - 1);
            } else {
                //cout << e << " " << a << " " << c << endl;
                upd(ro[c], mx, ro[e], ro[a], 1, 0, n - 1);
            }
            a = p[pl[a]];
        }
    };

    for(int i = 0; i < m; i++) {
        int t, a, b, c; rd(t, a, b, c);
        int l = q(a, b);
        apply(a, l, c, t == 2);
        apply(b, l, c, t == 2);
    }
    vector<bool> visited(7 * n);
    vector<bool> on_stack(7 * n);
    vector<int> topo;
    function<bool(int)> dfs3 = [&] (int s) {
        visited[s] = on_stack[s] = true;
        for (int u : nadj[s]) {
            if(on_stack[u]) {
                return true;
            } else if(!visited[u]) {
                if(dfs3(u)) return true;
            }
        }
        on_stack[s] = false;
        topo.pb(s);
        return false;
    };
    //for(int i = 0; i < nadj.size(); i++) {
    //    for(int u : nadj[i]) cout << i << " " << u << endl;
    //}
    for(int i = 0; i < n; i++) {
        if(!visited[i] && dfs3(i)) {
            cout << -1 << endl;
            return 0;
        }
    }
    reverse(topo.begin(), topo.end());
    int t = 0;
    vector<int> ans(n);
    for(int i : topo) {
        if(i < n) {
            ans[o[i] - 1] = ++t;
        }
    }
    for(int i : ans) cout << i << " ";
    cout << endl;
}