#include <cplib/general.h>
using namespace std;
const int LGV = 30;
const int INF = 1e9 + 1;


int v;
struct D {
    vector<int> ls, rs;
    int mxa;
    int mnb;
    D() {
        mxa = 0, mnb = INF;
        ls.resize(LGV, INF);
        rs.resize(LGV, INF);
    }
    D(int a, int b) {
        mxa = a, mnb = (b >= v) ? a : INF;
        ls.resize(LGV, INF);
        rs.resize(LGV, INF);
        for(int i = 0; i < LGV; i++) {
            if(getbit(b, i)) {
                ls[i] = mxa;
                rs[i] = mxa;
            }
        }
    }
};
void comb(D& a, D& b, D& c) {
    c.mxa = max(a.mxa, b.mxa);
    c.mnb = min(a.mnb, b.mnb);
    int cur = 0;
    for(int i = LGV - 1; i >= 0; i--) {
        if(getbit(v, i)) {
            cur = max(cur, min(a.rs[i], b.ls[i]));
        } else {
            c.mnb = min(c.mnb, max(cur, min(a.rs[i], b.ls[i])));
        }
    }
    c.mnb = min(c.mnb, cur);
    for(int i = 0; i < LGV; i++) {
        c.ls[i] = min(a.ls[i], max(b.ls[i], a.mxa));
        c.rs[i] = min(max(a.rs[i], b.mxa), b.rs[i]);
    }
}
struct SegT {
    int n;
    std::vector<D> t;
    SegT(int n) : n(n), t(2 * n, D()) {}
    void upd(int k, D u) {
        for (t[k += n] = u; k /= 2; ) comb(t[k * 2], t[k * 2 + 1], t[k]);
    }
    D query(int l, int r) {
        D L, R;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l&1) comb(L, t[l++], L);
            if (r&1) comb(t[--r], R, R);
        }
        comb(L, R, L);
        return L;
    }
};


void tc() {
    int n; rd(n, v);
    vector<int> a(n); rd(a);
    vector<int> b(n); rd(b);
    SegT segt(n);
    for(int i = 0; i < n; i++) {
        segt.upd(i, D(a[i], b[i]));
    }
    int q; rd(q);
    for(int i = 0; i < q; i++) {
        int t; rd(t);
        if(t == 1) {
            int k, x; rd(k, x);
            k--; b[k] = x;
            segt.upd(k, D(a[k], b[k]));
        } else {
            int l, r; rd(l, r); l--, r--;
            D res = segt.query(l, r);
            cout << (res.mnb == INF ? -1 : res.mnb) << " ";
        }
    }
    cout << '\n';
}

int main() {
    int t; rd(t);
    while(t--) tc();
}