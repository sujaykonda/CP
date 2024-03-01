#include <cplib/general.h>
using namespace std;

struct D {
    int v;
    int mn;
    int l, r;
    int lz;
    D() { v = 1, mn = 0, l = 0, r = 0, lz = 0; }
    friend D comb(D a, D b) {
        D c;
        c.mn = min(a.mn, b.mn);
        c.v = ((a.mn == c.mn) ? a.v : 0) + ((b.mn == c.mn) ? b.v : 0);
        c.l = a.l;
        c.r = b.r;
        return c;
    }
    friend D updD(D a, int u) {
        D c = a;
        c.lz += u;
        c.mn += u;
        c.l += u;
        c.r += u;
        return c;
    }
};

void tc() {
    int n; rd(n);
    vector<int> p(n); rd(p);
    vector<int> rp(n + 1);
    for(int i = 0; i < n; i++) rp[p[i]] = i;
    bool allinc = true;
    for(int i = 0; i < n; i++) {
        allinc = allinc && p[i] == i + 1;
    }
    if(allinc) {
        cout << n - 2 << endl;
        return;
    }
    vector<D> segt(4 * n);
    auto push = [&] (int s) {
        segt[2 * s] = updD(segt[2 * s], segt[s].lz);
        segt[2 * s + 1] = updD(segt[2 * s + 1], segt[s].lz);
        segt[s].lz = 0;
    };
    function<void(int, int, int, int, int, int)> upd = [&] (int u, int l, int r, int s, int lb, int rb) {
        l = max(lb, l);
        r = min(rb, r);
        if(l > r) return;
        if(l == lb && rb == r) {
            segt[s] = updD(segt[s], u);
            return;
        }
        int m = (lb + rb) / 2;
        push(s);
        upd(u, l, r, 2 * s, lb, m);
        upd(u, l, r, 2 * s + 1, m + 1, rb);
        segt[s] = comb(segt[2 * s], segt[2 * s + 1]);
    };
    for(int i = 0; i < n; i++) {
        upd(1, min(i + 1, p[i]), max(i + 1, p[i]), 1, 1, n);
    }
    int best = 0;
    auto testswap = [&] (int a, int b) {
        upd(-1, min(a + 1, p[a]), max(a + 1, p[a]), 1, 1, n);
        upd(-1, min(b + 1, p[b]), max(b + 1, p[b]), 1, 1, n);
        upd(1, min(a + 1, p[b]), max(a + 1, p[b]), 1, 1, n);
        upd(1, min(b + 1, p[a]), max(b + 1, p[a]), 1, 1, n);

        if(segt[1].mn == 1)
            best = max(best, segt[1].v);

        upd(-1, min(a + 1, p[b]), max(a + 1, p[b]), 1, 1, n);
        upd(-1, min(b + 1, p[a]), max(b + 1, p[a]), 1, 1, n);
        upd(1, min(a + 1, p[a]), max(a + 1, p[a]), 1, 1, n);
        upd(1, min(b + 1, p[b]), max(b + 1, p[b]), 1, 1, n);
    };
    //for(int i = 0; i < n; i++) {
    //    testswap(i, p[i] - 1);
    //}
    vector<int> suff(n); suff[n - 1] = p[n - 1];
    for(int i = n - 2; i >= 0; i--) {
        suff[i] = min(suff[i + 1], p[i]);
    }
    int mx = 0;
    for(int i = 0; i < n - 1; i++) {
        mx = max(mx, p[i]);
        testswap(rp[mx], rp[suff[i + 1]]);
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}