#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "TRUE" : "FALSE"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

string bessie = "bessie";

template<class T, T comb(T&, T&)> 
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
        if(r < lb || rb < l) return 0;
        if(l <= lb && rb <= r) return tr[s];
        int m = (lb + rb) / 2;
        return comb(query(l, r, 2 * s, lb, m), query(l, r, 2 * s, m + 1, rb));
    }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};

struct Data {
    ll ans = 0, bcnt = 0;
    array<ll, 6> cnt{}, nxt{}, mult{};
    Data() {}
    Data(ll rem, char c) {
        if(c == 'b')
            cnt[1] = 1;
        else
            cnt[0] = 1;
        for(int i = 5; i >= 0; i--) {
            nxt[i] = i;
            if(bessie[i] == c) {
                nxt[i] = (i + 1) % 6;
                if(i == 5) mult[i] = rem;
            }
        }
    }
};

Data comb(Data& a, Data& b) {
    Data d;
    // comb to sz, ans and bcnt
    d.ans = a.ans + b.ans;
    d.bcnt = a.bcnt + b.bcnt;
    // comb nxt
    for(int i = 0; i < 6; i++) {
        d.nxt[i] = b.nxt[a.nxt[i]];
    }
    // comb mult
    for(int i = 0; i < 6; i++) {
        d.mult[i] = b.mult[a.nxt[i]] + a.mult[i];
    }
    // comb cnt
    for(int i = 0; i < 6; i++) {
        d.cnt[b.nxt[i]] += a.cnt[i];
        d.cnt[i] += b.cnt[i];
    }
    // add to ans and bcnt
    for(int i = 0; i < 6; i++) {
        d.ans += b.mult[i] * a.cnt[i];
        d.bcnt += b.mult[i] * a.cnt[i];
    }
    return d;
}

int main() {
    string s; cin >> s;
    RecSegT<Data, comb> segt(s.size());
    for(int i = 0; i < s.size(); i++) {
        Data d = Data(s.size() - i, s[i]);
        segt.upd(i, d);
    }
    cout << segt.tr[1].ans << endl;
    int U; cin >> U;
    for(int i = 0; i < U; i++) {
        int k; char c; 
        cin >> k >> c;
        k--;
        Data d = Data(s.size() - k, c);
        segt.upd(k, d);
        cout << segt.tr[1].ans << endl;
    }
}
