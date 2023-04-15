#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
// divide and conquer SRQ (works on operations where a * b = b * a)
template<class T, T comb(T, T)>
struct SRQ : vector<vector<T>> {
    vector<T> v;
    SRQ(vector<T>& v) : v(v), vector<vector<T>>(lg(v.size()) + 1, vector<T>(v.size())) {
        for(int k = 1; k <= v.size(); k++) {
            // cool trick!
            int rad = 1, i = 0; while(k % (2 * rad) == 0) rad *= 2, i++;
            (*this)[i][k - 1] = v[k - 1];
            for(int j = k - 2; j >= k - rad; j--)
                (*this)[i][j] = comb((*this)[i][j + 1], v[j]);
            if(k < v.size()) (*this)[i][k] = v[k];
            for(int j = k + 1; j < v.size() && j < k + rad; j++)
                (*this)[i][j] = comb((*this)[i][j - 1], v[j]); 
        }
    }
    T query(int L, int R) {
        if(L == R) return v[L]; int i = lg(R ^ L);
        return comb((*this)[i][L], (*this)[i][R]);
    }
};

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

template<class T, T comb(T, T)> 
struct ItSegT {
    int n;
    vector<T> tr;
    ItSegT(int n) : n(n), tr(2 * n + 1) {}
    void mod(int k, T& u) {
        k += n, tr[k] = u;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = comb(tr[2 * k], tr[2 * k + 1]);
    }
    ll query(int a, int b) {
        a += n, b += n;
        T r = 1e9;
        while(a <= b) {
            if(a % 2 == 1) r = comb(tr[a++], r);
            if(b % 2 == 0) r = comb(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};

template<class T, T comb(T, T)> 
struct RecSegT {
    int n;
    vector<T> tr;
    RecSegT(int n) : n(n), tr(4 * n) {}
    void upd(int k, T& v, int s, int lb, int rb) {
        if(lb == k && rb == k) { tr[s] = v; return; }
        int m = (lb + rb) / 2;
        if(k <= m) upd(k, v, 2 * s, lb, m);
        else upd(k, v, 2 * s + 1, m + 1, rb);
        tr[s] = comb(tr[2 * s], tr[2 * s + 1]);
    }
    void upd(int k, T& v) { upd(k, v, 1, 0, n - 1); }
    T query(int l, int r, int s, int lb, int rb) {
        if(l > r) return 1e9;
        if(l == lb && rb == r) return tr[s];
        int m = (lb + rb) / 2;
        return comb(query(l, min(r, m), 2 * s, lb, m), query(max(l, m + 1), r, 2 * s + 1, m + 1, rb));
    }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};

int rmin(int a, int b) { return min(a, b); }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    //SRQ<int, rmin> srq(v);
    //SPT<int, rmin> srq(v);
    //ItSegT<int, rmin> segt(n);
    RecSegT<int, rmin> segt(n);
    
    for(int i = 0; i < n; i++) segt.upd(i, v[i]);
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; a--, b--;
        cout << segt.query(a, b) << endl;
    }
}