#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

const int MAXA = 5e6 + 1;
const int lgMAXA = 23;
array<int, MAXA> tot;
array<int, MAXA> depth;

// you can speed this up to log log W but not necessary
int lca(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    while(depth[a] > depth[b]) a = tot[a];
    while(a != b) a = tot[a], b = tot[b];
    return a;
}

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
// sparse table (works on operations where a * a * b = b)
template<class T, T comb(T, T)>
struct SPT : vector<vector<T>> {
    SPT(vector<T>& v) : vector<vector<T>>(lg(v.size()) + 1, vector<T>(v.size())) {
        (*this)[0] = v;
        for (int i = 0; i < lg(v.size()); i++)
            for (int j = 0; j <= v.size() - (1 << (i + 1)); j++)
                (*this)[i + 1][j] = comb((*this)[i][j], (*this)[i][j + (1 << i)]);
    }
    T query(int L, int R) {
        int i = lg(R - L + 1);
        return comb((*this)[i][L], (*this)[i][R - (1 << i) + 1]);
    }
};

struct SegT {
    int n;
    // store sum and min
    vector<pair<int, int>> tr;
    SegT(int n) : n(n), tr(2 * n + 1, {0, 0}) {}
    pair<int, int> comb(pair<int, int>& l, pair<int, int>& r) {
        return {l.first + r.first, min(l.second, r.second)};
    }
    void upd(int k, int u) {
        k += n, tr[k].first += u, tr[k].second += u;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = comb(tr[2 * k], tr[2 * k + 1]);
    }
    pair<int, int> query(int a, int b) {
        a += n, b += n;
        pair<int, int> r = {0, 25};
        while(a <= b) {
            if(a % 2 == 1) r = comb(tr[a++], r);
            if(b % 2 == 0) r = comb(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};

// dsu get
int get(int s, vector<int>& next, vector<bool>& good) {
    return good[s] ? s : (next[s] = get(next[s], next, good));
}

int main() {
    for(int i = 1; i < MAXA; i++)
        tot[i] = i;
    for(int i = 2; i < MAXA; i++) {
        if(tot[i] == i) {
            for(int j = i; j < MAXA; j += i)
                tot[j] -= tot[j] / i;
        }
    }
    depth[1] = 0;
    for(int i = 2; i < MAXA; i++)
        depth[i] = depth[tot[i]] + 1;
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    SPT<int, lca> spt(a);
    vector<int> adepth(n);
    for(int i = 0; i < n; i++) adepth[i] = depth[a[i]];
    SegT segt(n);
    for(int i = 0; i < n; i++) segt.upd(i, adepth[i]);
    vector<bool> good(n + 1); good[n] = true;
    vector<int> next(n);
    for(int i = 0; i < n; i++) next[i] = i + 1, good[i] = a[i] > 1;

    for(int i = 0; i < m; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if(t == 1) {
            int j = get(l, next, good);
            while(j <= r) {
                segt.upd(j, -1), adepth[j]--;
                if(adepth[j] == 0) good[j] = false;
                j = get(next[j], next, good);
            }
        } else {
            int lca = spt.query(l, r);
            pair<int, int> res = segt.query(l, r);
            cout << res.first - (r - l + 1) * min(res.second, depth[lca]) << endl;
        }
    }
}