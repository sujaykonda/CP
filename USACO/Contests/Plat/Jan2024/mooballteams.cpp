#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int HALF = (MOD + 1) / 2;
using ll = long long;
int bpow(int a, ll p) { return (p == 0) ? 1 : (((ll)bpow(((ll)a * a) % MOD, p / 2) * (p & 1 ? a : 1)) % MOD); }

struct SegT {
    int n;
    vector<int> v;
    vector<int> act;
    vector<int> lz;
    SegT(int _n) {
        n = _n;
        v.resize(4 * n);
        act.resize(4 * n);
        lz.resize(4 * n);
    }
    void build(vector<int>& nv, vector<int>& nact, int s, int lb, int rb) {
        lz[s] = 1;
        if(lb == rb) {
            v[s] = nv[lb];
            act[s] = nact[lb];
            return;
        }
        int m = (lb + rb) / 2;
        build(nv, nact, 2 * s, lb, m);
        build(nv, nact, 2 * s + 1, m + 1, rb);
        act[s] = 1;
        v[s] = (act[2 * s] * v[2 * s] + act[2 * s + 1] * v[2 * s + 1]) % MOD;
    }
    void build(vector<int>& nv, vector<int>& nact) { build(nv, nact, 1, 1, n); }
    void push(int s) {
        v[2 * s] = ((ll)v[2 * s] * lz[s]) % MOD;
        v[2 * s + 1] = ((ll)v[2 * s + 1] * lz[s]) % MOD;
        lz[2 * s] = ((ll)lz[2 * s] * lz[s]) % MOD;
        lz[2 * s + 1] = ((ll)lz[2 * s + 1] * lz[s]) % MOD;
        lz[s] = 1;
    }
    void upd(int m, int l, int r, int s, int lb, int rb) {
        l = max(lb, l);
        r = min(r, rb);
        if(r < l) return;
        if(l == lb && r == rb) {
            lz[s] = ((ll)lz[s] * m) % MOD;
            v[s] = ((ll)v[s] * m) % MOD;
            return;
        }
        int mb = (lb + rb) / 2;
        push(s);
        upd(m, l, r, 2 * s, lb, mb);
        upd(m, l, r, 2 * s + 1, mb + 1, rb);
        act[s] = 1;
        v[s] = (act[2 * s] * v[2 * s] + act[2 * s + 1] * v[2 * s + 1]) % MOD;
    }
    void toggleact(int k, int s, int lb, int rb) {
        if(k < lb || rb < k) return;
        if(lb == k && rb == k) {
            act[s] ^= 1;
            return;
        }
        int mb = (lb + rb) / 2;
        push(s);
        toggleact(k, 2 * s, lb, mb);
        toggleact(k, 2 * s + 1, mb + 1, rb);
        act[s] = 1;
        v[s] = (act[2 * s] * v[2 * s] + act[2 * s + 1] * v[2 * s + 1]) % MOD;
    }
    void toggleact(int k) { return toggleact(k, 1, 1, n); }
    void upd(int m, int l, int r) { upd(m, l, r, 1, 1, n); }
    int query(int l, int r, int s, int lb, int rb) {
        l = max(lb, l);
        r = min(r, rb);
        if(r < l) return 0;
        if(l == lb && r == rb) return act[s] * v[s];
        int m = (lb + rb) / 2;
        push(s);
        return (query(l, r, 2 * s, lb, m) + query(l, r, 2 * s + 1, m + 1, rb)) % MOD;
    }
    int query(int l, int r) { return query(l, r, 1, 1, n); }
};

int main() {
    int N; cin >> N;
    int ans = ((ll)(N - 1) * bpow(2, N) + 1) % MOD;
    int ans2 = ((ll)(N - 1) * bpow(2, N) + 1) % MOD;

    vector<int> xy(N + 1);
    for(int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        xy[x] = y;
    }
    SegT segt(N), rsegt(N);
    vector<int> iv1(N + 1), iv2(N + 1);
    vector<int> act1(N + 1, 1), act2(N + 1);
    iv1[0] = ((ll)HALF * HALF) % MOD;
    iv2[0] = ((ll)((ll)bpow(2, N) * HALF % MOD) * HALF) % MOD;
    for(int i = 1; i <= N; i++) {
        iv1[i] = (2 * iv1[i - 1]) % MOD;
        iv2[i] = ((ll)HALF * iv2[i - 1]) % MOD;
    }
    segt.build(iv1, act1);
    rsegt.build(iv2, act2);
    for(int i = 1; i <= N; i++) {
        segt.upd(((ll)HALF * HALF) % MOD, xy[i], N);
        segt.upd(2, 1, N);
        segt.toggleact(xy[i]);
        rsegt.upd(4, xy[i], N);
        rsegt.toggleact(xy[i]);
        rsegt.upd(HALF, 1, N);
        ans += MOD - segt.query(1, xy[i] - 1);
        ans %= MOD;
        ans += MOD - rsegt.query(xy[i] + 1, N);
        ans %= MOD;
        ans += MOD - (rsegt.query(xy[i], xy[i]) * 2 % MOD);
        ans %= MOD;
    }

    cout << (2 * ans) % MOD << endl;
}