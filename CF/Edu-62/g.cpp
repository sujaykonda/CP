#include <cplib/general.h>
using namespace std;

const ll INF = 1e18;

struct D {
    ll s;
    array<array<ll, 2>, 2> dp;
    friend D comb(D a, D b) {
        D nw;
        nw.s = b.s;
        nw.dp = {{{{INF, INF}}, {{INF, INF}}}};
        for(int i : {0, 1}) {
            for(int j : {0, 1}) {
                for(int k : {0, 1}) {
                    nw.dp[i][k] = min(nw.dp[i][k], a.dp[i][j] + b.dp[j][k]);
                }
            }
        }
        return nw;
    }
};

int main() {
    int n; rd(n);
    vector<ll> sw(n); rd(sw);
    vector<vector<array<ll, 3>>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        ll x, y, a, b; rd(x, y, a, b);
        x--, y--;
        adj[x].pb({y, a, b});
        adj[y].pb({x, a, b});
    }
    auto sp = [&] () {
        priority_queue<pair<ll, ll>> pq;
        vector<ll> nsw(n, -1);
        for(int i = 0; i < n; i++) pq.push({-sw[i], i});
        while(pq.size() > 0) {
            ll d = -pq.top().first;
            ll s = pq.top().second;
            pq.pop();
            if(nsw[s] != -1) continue;
            nsw[s] = d;
            for(auto [u, a, b] : adj[s]) {
                if(nsw[u] == -1) {
                    pq.push({-(d + a + b), u});
                }
            }
        }
        sw = nsw;
    };
    sp();
    vector<int> dep(n);
    vector<vector<D>> jmp(n, vector<D>(20));
    function<void(int, int, ll, ll)> dfs = [&] (int s, int e, ll a, ll b) {
        jmp[s][0].s = e;
        if(e != -1) {
            jmp[s][0].dp = {{{{a, sw[e] + a}}, {{sw[e] + b, b}}}};
        }
        int k = 0;
        while(jmp[s][k].s != -1) {
            jmp[s][k + 1] = comb(jmp[s][k], jmp[jmp[s][k].s][k]);
            k++;
        }
        for(k++; k < 20; k++) {
            jmp[s][k].s = -1;
        }
        for(auto [u, a2, b2] : adj[s]) {
            if(u != e) {
                dep[u] = dep[s] + 1;
                dfs(u, s, a2, b2);
            }
        }
    };
    dfs(0, -1, 0, 0);
    int q; rd(q);
    for(int qi = 0; qi < q; qi++) {
        int a, b; rd(a, b); a--, b--;
        if(dep[a / 2] < dep[b / 2]) {
            swap(a, b);
        }
        D l, r;
        l.s = a / 2;
        l.dp = {{{{0, sw[a / 2]}}, {{sw[a / 2], 0}}}};
        r.s = b / 2;
        r.dp = {{{{0, sw[b / 2]}}, {{sw[b / 2], 0}}}};
        for(int i = 19; i >= 0; i--) {
            if(jmp[l.s][i].s != -1 && dep[jmp[l.s][i].s] >= dep[b / 2]) {
                l = comb(l, jmp[l.s][i]);
            }
        }
        for(int i = 19; i >= 0; i--) {
            if(jmp[l.s][i].s != jmp[r.s][i].s) {
                l = comb(l, jmp[l.s][i]);
                r = comb(r, jmp[r.s][i]);
            }
        }
        if(l.s != r.s) {
            l = comb(l, jmp[l.s][0]);
            r = comb(r, jmp[r.s][0]);
        }
        ll ans = INF;
        for(int i : {0, 1}) {
            ans = min(ans, l.dp[a % 2][i] + r.dp[b % 2][i]);
        }
        cout << ans << "\n";
    }
}