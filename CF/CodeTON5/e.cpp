#include <cplib/ds/sparse/rurq.h>
using namespace std;
struct maxint { ll v; maxint() { v = 0; } maxint(ll _v) { v = _v; } 
    friend maxint operator+(maxint a, maxint b) { return maxint(max(a.v, b.v)); } 
    void set(maxint o) { v = o.v; }};
typedef _node_rurq<maxint, ll, ll> node;

void apply(ll u, node* n) {
    n->lz += u; n->d.v += u; }

void push(node* n) {
    n->left->d.v += n->lz;
    n->right->d.v += n->lz;
    n->left->lz += n->lz;
    n->right->lz += n->lz;
    n->lz = 0;
}

int main() {
    int n, k, A; cin >> n >> k >> A;
    ll sm = 0;
    vector<vector<pair<int, int>>> ps(k);
    for(int i = 0; i < n; i++) {
        int x, y, c; cin >> x >> y >> c;
        sm += c;
        ps[y].pb({x, c});
    }
    node* segt = new node(k);
    ll mxdp = 0;
    segt->upd(mxdp, 0, 0);
    for(int i = 1; i <= k; i++) {
        segt->upd(-A, 0, i - 1);
        for(auto [u, v] : ps[k - i])
            segt->upd(v, 0, u);
        mxdp = max(mxdp, segt->d.v);
        segt->upd(mxdp, i, i);
    }
    cout << sm - mxdp << endl;
}