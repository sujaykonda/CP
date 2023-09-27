#include <cplib/ds/bit.h>
#include <cplib/bs.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    vector<int> o(n); 
    for(int i = 0; i < n; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (int x, int y) { return a[x] < a[y]; });
    vector<int> ro(n); 
    for(int i = 0; i < n; i++) ro[o[i]] = i + 1;
    BIT lsm(n), lcnt(n), rsm(n), rcnt(n);
    for(int i = 0; i < n; i++) {
        rsm.add(ro[i], a[i]);
        rcnt.add(ro[i], 1);
    }
    ll best = 1e18;
    for(int i = 0; i < n; i++) {
        int m = bsmin(max(k - n + i, 0), min(i, k) - 1, [&] (int x) { 
            return lsm.sum(lcnt.lb(x)) > rsm.sum(rcnt.lb(k - x));
        });
        best = min(best, max(lsm.sum(lcnt.lb(m)), rsm.sum(rcnt.lb(k - m))));
        //cout << i << " " << m << " " << max(lsm.sum(lcnt.lb(m)), rsm.sum(rcnt.lb(k - m))) << endl;
        m--;
        if(m >= max(k - n + i, 0)) {
            best = min(best, max(lsm.sum(lcnt.lb(m)), rsm.sum(rcnt.lb(k - m))));
            //cout << i << " " << m << " " << max(lsm.sum(lcnt.lb(m)), rsm.sum(rcnt.lb(k - m))) << endl;
        }
        lsm.add(ro[i], a[i]);
        lcnt.add(ro[i], 1);
        rsm.add(ro[i], -a[i]);
        rcnt.add(ro[i], -1);
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}