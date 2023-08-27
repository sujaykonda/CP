#include <cplib/ds/sparse/segt.h>
using namespace std;
struct minint { int v; minint() : v(5e5) {} minint(int _v) : v(_v) {} 
    friend minint operator+(minint a, minint b) { return min(a.v, b.v); }};
struct smint {int v; smint() : v(0) {} smint(int _v) : v(_v) {}
    friend smint operator+(smint a, smint b) { return a.v + b.v; }};
const int MX = 1e5 + 1;
typedef _node_segt<minint> mnnode;
typedef _node_segt<smint> smnode;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    vector<int> L(n), R(n);
    mnnode* mnsegt = new mnnode(MX);
    for(int i = n - 1; i >= 0; i--) {
        L[i] = mnsegt->query(max(0, a[i] - k), a[i]).v;
        R[i] = mnsegt->query(a[i] + 1, min(MX, a[i] + k)).v;
        mnsegt->upd(a[i], minint(i));
    }
    del(mnsegt);
    vector<int> Lcnt(n), Rcnt(n);
    smnode* smsegt = new smnode(MX);
    for(int i = n - 1; i >= 0; i--) {
        if(L[i] < n)
            Lcnt[i] = Lcnt[L[i]] + smsegt->query(a[L[i]] + 1, a[i]).v + 1;
        if(R[i] < n)
            Rcnt[i] = Rcnt[R[i]] + smsegt->query(a[i] + 1, a[R[i]]).v;
        smsegt->upd(a[i], smsegt->query(a[i], a[i]) + 1);
    }
    del(smsegt);
    ll ans = 0;
    for(int i = 0; i < n; i++) ans += Lcnt[i] + Rcnt[i] + 1;
    cout << ans << endl;
}


int main() {
    int t; rd(t);
    while(t--) tc();
}
