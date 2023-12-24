#include <cplib/general.h>
#include <cplib/ds/srq.h>
using namespace std;
const int MX = 2e5;
struct D {
    ll fv, sv, fi;
    D() { fv = 0, sv = 0, fi = 0; }
};

D comb(D a, D b) {
    if(b.fv >= a.fv) {
        a.sv = a.fv, a.fv = b.fv, a.fi = b.fi;
        if(b.sv > a.sv) a.sv = b.sv;
    } else if(b.fv > a.sv) a.sv = b.fv;
    return a;
}

void tc() {
    int n; rd(n);
    vector<int> h(n), a(n); rd(h, a);
    vector<D> d(MX + 1);
    for(int i = 0; i < n; i++) {
        D c;
        c.fv = h[i], c.fi = i;
        d[a[i]] = comb(d[a[i]], c);
    }
    SRQ<D, comb> srq(d);
    vector<ll> ans(n);
    for(int x = 1; x <= MX; x++) {
        D cans;
        for(int i = 1; i * x - x + 1 <= MX; i++) {
            D c = srq.query(i * x - x + 1, min(i * x, MX));
            c.fv *= i, c.sv *= i;
            cans = comb(cans, c);
        }
        ans[cans.fi] = max(ans[cans.fi], cans.fv - cans.sv);
    }
    for(ll i : ans) cout << i << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}