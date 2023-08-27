#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

struct D {
    vector<int> v;
    int mult;
};
vector<D> d;
int N, K; 

void push(int s) {
    if(d[s].mult == 1) return;
    d[2 * s].mult = ((ll)d[2 * s].mult * d[s].mult) % MOD;
    d[2 * s + 1].mult = ((ll)d[2 * s + 1].mult * d[s].mult) % MOD;
    for(int i = 0; i <= K; i++) {
        d[2 * s].v[i] = ((ll)d[2 * s].v[i] * d[s].mult) % MOD;
        d[2 * s + 1].v[i] = ((ll)d[2 * s + 1].v[i] * d[s].mult) % MOD; 
    }
    d[s].mult = 1;
}
void pull(int s) {
    for(int i = 0; i <= K; i++) {
        d[s].v[i] = d[2 * s].v[i] + d[2 * s + 1].v[i], d[s].v[i] -= MOD * (d[s].v[i] >= MOD);
    }
}
vector<int> sum(int l, int r, int s, int lb, int rb) {
    l = max(l, lb), r = min(r, rb);
    if(r < l) return vector<int>(K + 1, 0);
    if(lb == l && r == rb) {
        return d[s].v;
    }
    push(s);
    int m = (lb + rb) / 2;
    vector<int> lsm = sum(l, r, 2 * s, lb, m);
    vector<int> rsm = sum(l, r, 2 * s + 1, m + 1, rb);
    for(int i = 0; i <= K; i++) lsm[i] += rsm[i], lsm[i] -= MOD * (lsm[i] >= MOD);
    return lsm;
}
void mod(int k, vector<int>& v, int s, int lb, int rb) {
    if(k < lb || rb < k) return;
    if(lb == k && k == rb) {
        d[s].v = v;
        return;
    }
    push(s);
    int m = (lb + rb) / 2;
    mod(k, v, 2 * s, lb, m);
    mod(k, v, 2 * s + 1, m + 1, rb);
    pull(s);
}
void mult(int l, int r, int v, int s, int lb, int rb) {
    l = max(l, lb), r = min(r, rb);
    if(r < l) return;
    if(lb == l && r == rb) {
        d[s].mult = ((ll)d[s].mult * v) % MOD;
        for(int i = 0; i <= K; i++) d[s].v[i] = ((ll)d[s].v[i] * v) % MOD;
        return;
    }
    push(s);
    int m = (lb + rb) / 2;
    mult(l, r, v, 2 * s, lb, m);
    mult(l, r, v, 2 * s + 1, m + 1, rb);
    pull(s);
}

int main() {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> K;
    d.resize(8 * N, D{vector<int>(K + 1), 1});

    // precompute K chooses
    vector<vector<int>> ch(K + 1, vector<int>(K + 1));
    ch[0][0] = 1;
    for(int i = 0; i < K; i++) {
        for(int j = 0; j <= i; j++) {
            ch[i + 1][j] += ch[i][j];
            ch[i + 1][j + 1] += ch[i][j];
            ch[i + 1][j] -= MOD * (ch[i + 1][j] >= MOD);
            ch[i + 1][j + 1] -= MOD * (ch[i + 1][j] >= MOD);
        }
    }

    vector<int> r(2 * N + 1);
    for(int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        r[a] = b;
    }
    for(int i = 1; i <= 2 * N; i++) {
        if(r[i] == 0) continue;
        mult(r[i] + 1, 2 * N, 2, 1, 1, 2 * N);
        vector<int> sums = sum(0, i - 1, 1, 1, 2 * N);
        vector<int> nv = sum(i, r[i], 1, 1, 2 * N);
        for(int j = 0; j <= K; j++) {
            nv[j]++;
            for(int k = 0; k <= j; k++) {
                nv[j] = (nv[j] + (ll)sums[k] * ch[j][k]) % MOD;
            }
        }
        mod(r[i], nv, 1, 1, 2 * N);
    }
    cout << d[1].v[K] << endl;
}