#include <cplib/general.h>
using namespace std;

// generic sparse RURQ
struct node {
    int mx, lz;
    ll lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb) { left = right = NULL; mx = 0, lz = 0; }

    // propogate lazy info downward
    void push() {
        left->mx += lz;
        left->lz += lz;
        right->mx += lz;
        right->lz += lz;
        lz = 0;
    }

    // creates the child nodes
    void cc() {
        ll m = (lb + rb) / 2;
        if(!left) left = new node(lb, m);
        if(!right) right = new node(m + 1, rb);
    }

    // update
    void upd(int u, ll l, ll r) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { mx += u, lz += u; return; }
        cc(), push();
        left->upd(u, l, r);
        right->upd(u, l, r);
        mx = max(left->mx, right->mx);
    }

    // querying
    int query(ll l, ll r) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) { return 0; }
        if(l == lb && r == rb) return mx;
        cc(), push();
        return max(left->query(l, r), right->query(l, r));
    }
};


void tc() {
    int n; rd(n);
    vector<int> p(n);
    adjlist adj(n);
    for(int i = 1; i < n; i++) {
        rd(p[i]); p[i]--;
        adj[p[i]].pb(i);
    }
    vector<int> a(n); rd(a);
    for(int i = 0; i < n; i++) a[i]--;
    vector<int> o;
    vector<int> in(n), out(n);
    adjlist adj2(n);
    vector<int> last(n, -1);
    function<void(int)> dfs = [&] (int s) {
        in[s] = o.size();
        o.push_back(s);
        int prev = last[a[s]];
        if(prev != -1)
            adj2[prev].pb(s);
        last[a[s]] = s;
        for(int u : adj[s]) {
            dfs(u);
        }
        last[a[s]] = prev;
        out[s] = o.size() - 1;
    };
    dfs(0);
    ll ans = 0;
    node* segt = new node(0, n - 1);
    for(int i = n - 1; i >= 0; i--) {
        segt->upd(1, in[i], out[i]);
        for(int u : adj2[i]) {
            segt->upd(-1, in[u], out[u]);
        }
        int mx = 1;
        int mx2 = 1;
        for(int u : adj[i]) {
            int v = segt->query(in[u], out[u]);
            if(v > mx) mx2 = mx, mx = v;
            else if(v > mx2) mx2 = v;
        }
        ans = max(ans, (ll) mx * mx2);
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}