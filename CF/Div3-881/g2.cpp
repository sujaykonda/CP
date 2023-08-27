#include <cplib/general.h>
using namespace std;

struct D {
    int i, v;
    int mnp, mxp;
    int mns, mxs;
    int mnv, mxv;
};

D comb(D a, D b) {
    D c; c.i = b.i;
    c.v = a.v + b.v;
    c.mnp = min(a.mnp, a.v + b.mnp);
    c.mxp = max(a.mxp, a.v + b.mxp);
    c.mns = min(b.mns, b.v + a.mns);
    c.mxs = max(b.mxs, b.v + a.mxs);
    c.mnv = min({a.mnv, b.mnv, a.mns + b.mnp});
    c.mxv = max({a.mxv, b.mxv, a.mxs + b.mxp});
    return c;
}

void tc() {
    int n; rd(n);
    vector<int> p(2), x(2); x[1] = 1;
    vector<pair<pair<int, int>, int>> q;
    for(int i = 0; i < n; i++) {
        string s; rd(s);
        if(s[0] == '+') {
            int v, _x; rd(v, _x);
            p.pb(v), x.pb(_x); 
        } else {
            int u, v, k; rd(u, v, k);
            q.pb({{u, v}, k});
        }
    }
    vector<int> d(p.size()); d[0] = -1;
    for(int i = 1; i < p.size(); i++) d[i] = d[p[i]] + 1;
    vector<vector<D>> jmp(lg(p.size()) + 1, vector<D>(p.size()));
    for(int i = 1; i < p.size(); i++) {
        jmp[0][i].i = p[i];
        jmp[0][i].v = x[i];
        jmp[0][i].mnv = jmp[0][i].mnp = jmp[0][i].mns = min(0, x[i]);
        jmp[0][i].mxv = jmp[0][i].mxp = jmp[0][i].mxs = max(0, x[i]);
    }
    for(int i = 0; i < jmp.size() - 1; i++) {
        for(int j = 1; j < p.size(); j++) {
            jmp[i + 1][j] = comb(jmp[i][j], jmp[i][jmp[i][j].i]);
        }
    }

    for(auto [u, v] : q) {
        int a = u.first, b = u.second;
        if(d[a] < d[b]) swap(a, b);
        D da, db;
        da.i = a;
        da.v = da.mnp = da.mxp = da.mns = da.mxs = da.mnv = da.mxv = 0;
        db.i = b;
        db.v = db.mnp = db.mxp = db.mns = db.mxs = db.mnv = db.mxv = 0;
        for(int i = jmp.size() - 1; i >= 0; i--) {
            if(d[jmp[i][da.i].i] >= d[db.i]) {
                da = comb(da, jmp[i][da.i]);
            }
        }
        for(int i = jmp.size() - 1; i >= 0; i--) {
            if(jmp[i][da.i].i != jmp[i][db.i].i) {
                da = comb(da, jmp[i][da.i]);
                db = comb(db, jmp[i][db.i]);
            }
        }
        if(da.i != db.i) {
            da = comb(da, jmp[0][da.i]);
            db = comb(db, jmp[0][db.i]);
        }
        int mnv = min({da.mnv, db.mnv, da.mns + x[da.i] + db.mns});
        int mxv = max({da.mxv, db.mxv, da.mxs + x[da.i] + db.mxs});
        if(mnv <= v  && v <= mxv) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}