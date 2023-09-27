#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
const int MX = 2e5;
 
struct line {
    ll l, r, m, b;
    ll y_inter_cl(int y) {
        return (y - b + m - 1) / m;
    }
    ll y_inter_fr(int y) {
        return (y - b) / m;
    }
};
line comb(line a, line b) {
    line c;
    c.m = b.m * a.m;
    c.b = b.m * a.b + b.b;
    c.l = max(a.l, a.y_inter_cl(b.l));
    c.r = min(a.r, a.y_inter_fr(b.r));
    if(c.m > MX) {
        ll y = c.l * c.m + c.b;
        c.m = MX + 1;
        c.b = y - c.l * c.m; 
    }
    return c;
}
line add(line a, line b) {
    line c;
    c.m = a.m + b.m;
    c.b = a.b + b.b;
    c.l = max(a.l, b.l);
    c.r = min(a.r, b.r);
    return c;
}
const vector<line> none{line{1, MX, 1, 0}};
const vector<line> zero{line{1, MX, 0, 0}};
 
// computes b(a(x))
void merge(vector<line>& a, vector<line>& b, vector<line>& c) {
    int j = 0;
    for(int i = 0; i < a.size(); i++) {
        while(j < b.size() && a[i].y_inter_fr(b[j].r) <= a[i].r) {
            line nc = comb(a[i], b[j]);
            if(nc.l <= nc.r)
                c.push_back(nc);
            j++;
        }
        if(j < b.size()) {
            line nc = comb(a[i], b[j]);
            if(nc.l <= nc.r)
                c.push_back(nc);
        }
    }
}
 
// computes b(a(x)) + c(x)
void addmerge(vector<line>& a, vector<line>& b, vector<line>& c, vector<line>& d) {
    if(a.size() == 0 || b.size() == 0) return;

    int j = 0, k = 0;
    auto addm = [&] (line nw) {
        while(k < c.size() && c[k].r <= nw.r) {
            line nw2 = add(nw, c[k]);
            if(nw.l <= nw.r) {
                d.push_back(nw2);
            }
            k++;
        }
        if(k < c.size()) {
            line nw2 = add(nw, c[k]);
            if(nw2.l <= nw2.r)
                d.push_back(nw2);
        }
    };
    for(int i = 0; i < a.size(); i++) {
        while(j < b.size() && a[i].y_inter_fr(b[j].r) <= a[i].r) {
            line nw = comb(a[i], b[j]);
            if(nw.l <= nw.r) {
                addm(nw);
            }
            j++;
        }
        if(j < b.size()) {
            line nw = comb(a[i], b[j]);
            if(nw.l <= nw.r) {
                addm(nw);
            }
        }
    }
}
 
struct SegT {
    int n;
    vector<vector<line>> left;
    vector<vector<line>> zeros;
    SegT(int _n) {
        n = 1;
        while(n < _n) n *= 2;
        left.resize(2 * n + 1, none);
        zeros.resize(2 * n + 1, zero);
    }
    void mod(int k, vector<line>& u_left, vector<line>& u_zeros) {
        k += n;
        left[k] = u_left;
        zeros[k] = u_zeros;
        for (k /= 2; k > 0; k /= 2) {
            left[k].clear();
            merge(left[k * 2], left[k * 2 + 1], left[k]);
            zeros[k].clear();
            addmerge(left[k * 2], zeros[k * 2 + 1], zeros[k * 2], zeros[k]);
        }
    }
};
 
void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
 
    vector<int> ans(n);
    ans[0] = max(1, a[0]);
    if(n == 1) {
        cout << ans[0] << '\n';
        return;
    }
 
    for(int i = 0; i < n; i++)
        if(a[i] > n) a[i] = 0;
    SegT segt(n + 1);
    vector<int> cnt(n + 1);
    auto upd = [&] (int k) {
        vector<line> zeros{line{1, MX, 0, 0}};
        vector<line> lines{line{1, MX / 2, 2, 0}};
        if(cnt[k] > 0) {
            zeros = {line{1, cnt[k], -1, cnt[k]}, line{cnt[k] + 1, MX, 0, 0}};
            lines = {line{1, cnt[k], 1, 0}, line{cnt[k] + 1, (MX + cnt[k]) / 2, 2, -cnt[k]}};
        }
        segt.mod(n - k + 1, lines, zeros);
    };
 
    int m = 3;
    int zeros = 0;
    cnt[a[0]]++;
    if(a[0] == 0 || a[0] >= m) zeros++;
    upd(1);
    upd(2);
    for(int i = 1; i < n; i++) {
        cnt[a[i]]++;
        if(0 < a[i] && a[i] < m) upd(a[i]);
        else zeros++;
        while(segt.left[1].size() > 0 && segt.left[1][0].b + segt.left[1][0].m <= segt.zeros[1][0].b + segt.zeros[1][0].m + zeros) {
            upd(m);
            zeros -= cnt[m];
            m++;
        }
        ans[i] = m - 1;
    }
    for(int i : ans) cout << i << " ";
    cout << '\n';
}
 
int main() {
    int t; rd(t);
    while(t--) tc();
}
