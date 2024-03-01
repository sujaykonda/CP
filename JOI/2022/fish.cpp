#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 1e5 + 1;
const ll INF = 1e18;

// count min segtree
const int SEGTSZ = 2 << 17;
struct D {
    int cnt, mn, lz;
} segt[SEGTSZ];


void pull(int s) {
    segt[s].mn = min(segt[2 * s].mn, segt[2 * s + 1].mn);
    segt[s].cnt = (segt[2 * s].mn == segt[s].mn ? segt[2 * s].cnt : 0) + (segt[2 * s + 1].mn == segt[s].mn ? segt[2 * s + 1].cnt : 0);
    segt[s].mn += segt[s].lz;
}

void build(int s, int lb, int rb) {
    if(lb == rb) {
        segt[s].cnt = 1;
        return;
    }
    int m = (lb + rb) / 2;
    build(2 * s, lb, m);
    build(2 * s + 1, m + 1, rb);
    pull(s);
}

void upd(int u, int l, int r, int s, int lb, int rb) {
    l = max(lb, l), r = min(rb, r);    
    if(r < l) return;
    if(l == lb && r == rb) {
        segt[s].lz += u;
        segt[s].mn += u;
        return;
    }
    int m = (lb + rb) / 2;
    upd(u, l, r, 2 * s, lb, m);
    upd(u, l, r, 2 * s + 1, m + 1, rb);
    pull(s);
}

pair<int, int> query(int l, int r, int s, int lz, int lb, int rb) {
    l = max(lb, l), r = min(rb, r);    
    if(r < l) return {1e9, 0};
    if(l == lb && r == rb) {
        return {segt[s].mn + lz, segt[s].cnt};
    }
    int m = (lb + rb) / 2;
    lz += segt[s].lz;
    auto lres = query(l, r, 2 * s, lz, lb, m);
    auto rres = query(l, r, 2 * s + 1, lz, m + 1, rb);
    if(lres.first > rres.first) swap(rres, lres);
    lres.second += (lres.first == rres.first) ? rres.second : 0;
    return lres;
}

// go as left / right as possible
struct D2 {
    ll sm, mn;
} lsegt[SEGTSZ], rsegt[SEGTSZ];

void lupd(ll u, int k, int s, int lb, int rb) {
    if(k == lb && rb == k) {
        lsegt[s].sm += u;
        lsegt[s].mn += u;
        return;
    }
    int m = (lb + rb) / 2;
    if(k <= m) {
        lupd(u, k, 2 * s, lb, m);
    } else {
        lupd(u, k, 2 * s + 1, m + 1, rb);
    }
    lsegt[s].mn = min(lsegt[2 * s].mn, lsegt[2 * s].sm + lsegt[2 * s + 1].mn);
    lsegt[s].sm = lsegt[2 * s].sm + lsegt[2 * s + 1].sm;
}

void rupd(ll u, int k, int s, int lb, int rb) {
    if(k == lb && rb == k) {
        rsegt[s].sm += u;
        rsegt[s].mn += u;
        return;
    }
    int m = (lb + rb) / 2;
    if(k <= m) {
        rupd(u, k, 2 * s, lb, m);
    } else {
        rupd(u, k, 2 * s + 1, m + 1, rb);
    }
    rsegt[s].mn = min(rsegt[2 * s + 1].mn, rsegt[2 * s + 1].sm + rsegt[2 * s].mn);
    rsegt[s].sm = rsegt[2 * s].sm + rsegt[2 * s + 1].sm;
}

ll lquery(int l, int r, int s, int lb, int rb) {
    l = max(l, lb), r = min(r, rb);
    if(r < l) return 0;
    if(l == lb && r == rb) {
        return lsegt[s].sm;
    }
    int m = (lb + rb) / 2;
    return lquery(l, r, 2 * s, lb, m) + lquery(l, r, 2 * s + 1, m + 1, rb);
}
ll rquery(int l, int r, int s, int lb, int rb) {
    l = max(l, lb), r = min(r, rb);
    if(r < l) return 0;
    if(l == lb && r == rb) {
        return rsegt[s].sm;
    }
    int m = (lb + rb) / 2;
    return rquery(l, r, 2 * s, lb, m) + rquery(l, r, 2 * s + 1, m + 1, rb);
}

ll lfind(ll v, int l, int& r, int s, int lb, int rb) {
    if(rb < l) return v;
    if(lb == rb && v + lsegt[s].sm < 0) {
        r = lb;
        return v + lsegt[s].sm;
    }
    if(l <= lb && v + lsegt[s].mn >= 0) {
        return v + lsegt[s].sm;
    }
    int m = (lb + rb) / 2;
    v = lfind(v, l, r, 2 * s, lb, m);
    if(r == -1) {
        v = lfind(v, l, r, 2 * s + 1, m + 1, rb);
    }
    return v;
}

ll rfind(ll v, int r, int& l, int s, int lb, int rb) {
    if(r < lb) return v;
    if(lb == rb && v + rsegt[s].sm < 0) {
        l = lb;
        return v + rsegt[s].sm;
    }
    if(rb <= r && v + rsegt[s].mn >= 0) {
        return v + rsegt[s].sm;
    }
    int m = (lb + rb) / 2;
    v = rfind(v, r, l, 2 * s + 1, m + 1, rb);
    if(l == -1) {
        v = rfind(v, r, l, 2 * s, lb, m);
    }
    return v;
}

int N; 
int A[MXN];

void comp(int k, int u) {
    int l = k, r = k;
    if((l == 1 || (A[l - 1] > A[l])) && (r == N || (A[r + 1] > A[r]))) {
        // cout << l << " " << r << " " << u << endl;
        upd(u, l, r, 1, 1, N);
    }
    while(1 < l || r < N) {
        if(l == 1 || (r != N && A[r + 1] < A[l - 1])) {
            int nr = -1;
            lfind(lquery(l, r, 1, 1, N) - A[l], r + 1, nr, 1, 1, N);
            r = nr;
        } else {
            int nl = -1;
            rfind(rquery(l, r, 1, 1, N) - A[r], l - 1, nl, 1, 1, N);
            l = nl;
        }
        if(rquery(l, r, 1, 1, N) - A[r] < 0 && lquery(l, r, 1, 1, N) - A[l] < 0) {
            // cout << l << " " << r << " " << u << endl;
            upd(u, l, r, 1, 1, N);
        }
    }
    r = k;
    while(true) {
        int nr = -1;
        lfind(lquery(k + 1, r, 1, 1, N) - A[k + 1], r + 1, nr, 1, 1, N);
        r = nr;
        if(rquery(k + 1, r, 1, 1, N) - A[r] >= 0) break;
        upd(u, k + 1, r, 1, 1, N);
        if(r >= N) break;
    }
    l = k;
    while(true) {
        int nl = -1;
        rfind(rquery(l, k - 1, 1, 1, N) - A[k - 1], l - 1, nl, 1, 1, N);
        l = nl;
        if(lquery(l, k - 1, 1, 1, N) - A[l] >= 0) break;
        upd(u, l, k - 1, 1, 1, N);
        if(l <= 1) break;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i < N; i++) {
        lupd(2 * A[i] - A[i + 1], i, 1, 1, N);
    }
    lupd(-INF, N, 1, 1, N);
    for(int i = N; i >= 2; i--) {
        rupd(2 * A[i] - A[i - 1], i, 1, 1, N);
    }
    rupd(-INF, 1, 1, 1, N);
    for(int i = 1; i <= N; i++) {
        int r = i - 1;
        while(true) {
            int nr = -1;
            lfind(lquery(i, r, 1, 1, N) - A[i], r + 1, nr, 1, 1, N);
            r = nr;
            if(rquery(i, r, 1, 1, N) - A[r] >= 0) break;
            upd(1, i, r, 1, 1, N);
            if(r >= N) break;
        }
    }
    build(1, 1, N);
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y;
            comp(x, -1);
            int del = y - A[x];
            A[x] = y;
            if(x < N) lupd(2 * del, x, 1, 1, N);
            if(x > 1) rupd(2 * del, x, 1, 1, N);
            if(x > 1) lupd(-del, x - 1, 1, 1, N);
            if(x < N) rupd(-del, x + 1, 1, 1, N);
            comp(x, 1);
        } else {
            int L, R; cin >> L >> R;
            int r = L - 1;
            while(true) {
                int nr = -1;
                lfind(lquery(L, r, 1, 1, N) - A[L], r + 1, nr, 1, 1, N);
                if(nr >= R) break;
                r = nr;
            }
            r++;
            int l = R + 1;
            while(true) {
                int nl = -1;
                rfind(rquery(l, R, 1, 1, N) - A[R], l - 1, nl, 1, 1, N);
                if(nl <= L) break;
                l = nl;
            }
            l--;
            // cout << r << " " << l << endl;
            cout << query(r, l, 1, 0, 1, N).second << '\n';
        }
    }
}