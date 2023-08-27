#include <cplib/bs.h>
#include <cplib/ds/srq.h>
using namespace std;
template<class T> T _min(T a, T b) { return min(a, b); }
template<class T> T _max(T a, T b) { return max(a, b); }
struct D {
    int v, lz;
};
vector<D> d;

void push(int s, int lb, int rb) {
    if(d[s].lz == -1) return;
    int m = (lb + rb) / 2;
    d[2 * s].v = d[s].lz * (m - lb + 1);
    d[2 * s + 1].v = d[s].lz * (rb - m);
    d[2 * s].lz = d[2 * s + 1].lz = d[s].lz;
    d[s].lz = -1;
}

void updrange(int v, int l, int r, int s, int lb, int rb) {
    l = max(l, lb), r = min(r, rb);
    if(r < l) return;
    if(l == lb && rb == r) {
        d[s].lz = v;
        d[s].v = v * (rb - lb + 1);
        return;
    }
    push(s, lb, rb);
    int m = (lb + rb) / 2;
    updrange(v, l, r, 2 * s, lb, m);
    updrange(v, l, r, 2 * s + 1, m + 1, rb);
    d[s].v = d[2 * s].v + d[2 * s + 1].v;
}

int main() {
    int n; rd(n);
    d.resize(4 * n);
    vector<int> p(n); rd(p);
    SRQ<int, _min> mnsrq(p);
    SRQ<int, _max> mxsrq(p);
    ll ans = 0;
    for(int i = 1; i < n; i++) {
        if(p[i] > p[i - 1]) {
            int j = bsmin(0, i - 1, [&] (int x) { return mxsrq.query(x, i) == p[i]; });
            updrange(1, j, i - 1, 1, 0, n - 1);
        } else {
            int j = bsmin(0, i - 1, [&] (int x) { return mnsrq.query(x, i) == p[i]; });
            updrange(0, j, i - 1, 1, 0, n - 1);
        }
        ans += d[1].v;
    }
    cout << ans << endl;
}