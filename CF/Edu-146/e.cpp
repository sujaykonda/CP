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

struct Arr : array<array<ll, 2>, 2> {
    Arr() {
        (*this)[0] = {0, 0};
        (*this)[1] = {0, 0};
    }
    Arr(ll v) : Arr() {
        (*this)[0][1] = v;
    }
};

// sparse
template<class T, T comb(T&, T&)> struct node {
    T val;
    node *left, *right;
    node() : val() { left = right = NULL; }
    inline node* leftc() { if(!left) left = new node(); return left; }
    inline node* rightc() { if(!right) right = new node(); return right; }
    void upd(ll k, T v, ll lb, ll rb) {

        if(lb == k && rb == k) { val = v; return; }
        ll m = (lb + rb) / 2;
        if(k <= m) leftc()->upd(k, v, lb, m);
        else rightc()->upd(k, v, m + 1, rb);
        val = comb(leftc()->val, rightc()->val);
    }
    T query(ll l, ll r, ll lb, ll rb) {
        if(r < lb || rb < l) return 0;
        if(l <= lb && rb <= r) return val;
        ll m = (lb + rb) / 2;
        T re;
        if(left) re = comb(left->query(l, r, lb, m), re);
        if(right) re = comb(re, right->query(l, r, m + 1, rb));
        return re;
    }
};

Arr comb(Arr& a, Arr& b) {
    Arr nw;
    for(int k = 0; k < 2; k++)
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                nw[i][j] = max(nw[i][j], a[i][k] + b[k][j]);
    return nw;
}

int main() {
    int n; cin >> n;
    ll sum = 0;
    vector<ll> a(n);
    for(int i = 1; i < n; i++) cin >> a[i], sum += a[i];
    node<Arr, comb>* segt = new node<Arr, comb>();
    for(int i = 2; i < n - 1; i++) {
        Arr arr(a[i]);
        segt->upd(i, arr, 0, n - 1);
    }
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll k, x; cin >> k >> x;
        sum += x - a[k];
        a[k] = x;
        if(k != 1 && k != n - 1) {
            Arr arr(a[k]);
            segt->upd(k, arr, 0, n - 1);
        }
        Arr ans = segt->val;
        cout << 2 * (sum - ans[0][1]) << endl;
    }
}