#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char c) { return string(1, c); } string str(_Bit_reference b) { return b ? "T" : "F"; }
string str(int x) { return to_string(x); } string str(ll x) { return to_string(x); }
template<class T> string str(T a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

struct ItSegT {
    struct Data { int v = -2e5; };
    Data comb(Data a, Data b) {
        return Data{max(a.v, b.v)};
    }

    int n;
    vector<Data> tr;
    ItSegT(int n) : n(n), tr(2 * n + 1) {}
    void upd(int k, Data u) {
        k += n, tr[k] = u;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = comb(tr[2 * k], tr[2 * k + 1]);
    }
    Data query(int a, int b) {
        a += n, b += n;
        Data r;
        while(a <= b) {
            if(a % 2 == 1) r = comb(tr[a++], r);
            if(b % 2 == 0) r = comb(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};

int segmin(int a, int b) { return min(a, b); }

int main() {
    int n; cin >> n;
    vector<int> a(n); cin >> a;
    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) 
        p[i + 1] = p[i] + a[i];
    vector<int> o(n + 1); 
    for(int i = 0; i <= n; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (int a, int b) { return p[a] == p[b] ? a < b : p[a] < p[b]; });
    vector<int> ro(n + 1);
    for(int i = 0; i <= n; i++) ro[o[i]] = i;
    ItSegT segt(n + 1);
    for(int i = n; i >= 0; i--) segt.upd(ro[i], ItSegT::Data{-i});
    int last = 0;
    for(int i = 1; i <= n; i++) {
        int segres = segt.query(0, ro[i]).v;
        last = max(last - 1, segres);
        segt.upd(ro[i], ItSegT::Data{last});
    }
    cout << n + last << endl;
}