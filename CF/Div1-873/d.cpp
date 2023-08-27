#include <cplib/general.h>
using namespace std;

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
};

void tc() {
    int n; rd(n);
    vector<vector<int>> jmp(lg(n) + 1, vector<int>(n + 1));
    adjlist adj(n + 1);
    vector<int> dep(n + 1); dep[0] = -1;
    for(int i = 2; i <= n; i++) {
        rd(jmp[0][i]);
        for(int j = 0; j < lg(n); j++)
            jmp[j + 1][i] = jmp[j][jmp[j][i]];
        dep[i] = dep[jmp[0][i]] + 1;
        adj[jmp[0][i]].pb(i);
    }
    int t = 1;
    vector<int> st(n + 1), en(n + 1);
    auto dfs = [&] (int s, auto&& dfs) {
        if(s == 0) return;
        st[s] = t++;
        for(int u : adj[s])
            dfs(u, dfs);
        en[s] = t - 1;
    };
    dfs(1, dfs);

    BIT bit(t);
    bit.add(st[1], 1);
    auto sz = [&] (int s) { return bit.sum(en[s]) - bit.sum(st[s] - 1); };
    int cen = 1;
    ll ans = n;

    for(int i = 2; i <= n; i++) {
        bit.add(st[i], 1);
        if(en[cen] >= st[i] && st[i] >= st[cen]) {
            int b = i;
            for(int j = lg(n); j >= 0; j--)
                if(dep[cen] < dep[jmp[j][b]])
                    b = jmp[j][b];
            if(sz(b) > i / 2) {
                cen = b;
                ans = 2 * sz(cen) - i;
            } else {
                ans = min(ans, i - 2 * sz(b));
            }
        } else {
            if(i - sz(cen) > i / 2) {
                ans = i - 2 * sz(cen);
                cen = jmp[0][cen];
            }
        }
        ans = min(ans, 2 * sz(cen) - i);
        cout << ans << " ";
        ans++;
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}