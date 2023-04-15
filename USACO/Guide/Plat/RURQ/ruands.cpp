#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int& a) { return to_string(a); } string str(ll& a) { return to_string(a); }
string str(char& a) { return to_string(a); } string str(_Bit_reference& a) { return to_string(a); }
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

// norm
struct RURQ {
    int n;
    vector<ll> tr;
    vector<ll> lzset, lzadd;
    RURQ(int n) : n(n), tr(4 * n, 0), lzset(4 * n), lzadd(4 * n) {}
    void push(int s, int l, int r) {
        int m = (l + r) / 2;
        if(lzset[s] != 0) {
            tr[2 * s] = (ll)(m - l + 1) * lzset[s];
            tr[2 * s + 1] = (ll)(r - m) * lzset[s];
            lzset[2 * s] = lzset[2 * s + 1] = lzset[s];
            lzadd[2 * s] = lzadd[2 * s + 1] = 0;
            lzset[s] = 0;
        }
        else {
            tr[2 * s] += (ll)(m - l + 1) * lzadd[s];
            if(lzset[2 * s] == 0) lzadd[2 * s] += lzadd[s];
            else lzset[2 * s] += lzadd[s], lzadd[2 * s] = 0;
            tr[2 * s + 1] += (ll)(r - m) * lzadd[s];
            if(lzset[2 * s + 1] == 0) lzadd[2 * s + 1] += lzadd[s];
            else lzset[2 * s + 1] += lzadd[s], lzadd[2 * s + 1] = 0;
            lzadd[s] = 0;
        }
    }
    void pull(int s) {
        tr[s] = tr[s * 2] + tr[s * 2 + 1];
    }
    void updset(int s, int l, int r, int lb, int rb, ll v) {
        if(l > r) return;
        if(l == lb && rb == r) {
            tr[s] = v * (ll)(rb - lb + 1); 
            lzset[s] = v; 
            lzadd[s] = 0;
        } else {
            push(s, lb, rb);
            int m = (lb + rb) / 2;
            updset(s * 2, l, min(r, m), lb, m, v);
            updset(s * 2 + 1, max(l, m + 1), r, m + 1, rb, v);
            pull(s);
        }
    }
    void updset(int l, int r, int v) { updset(1, l, r, 0, n - 1, v); }
    void updadd(int s, int l, int r, int lb, int rb, ll v) {
        if(l > r) return;
        if(l == lb && rb == r) {
            tr[s] += v * (ll)(rb - lb + 1);
            if(lzset[s] == 0) lzadd[s] += v;
            else lzset[s] += v;
        } else {
            push(s, lb, rb);
            int m = (lb + rb) / 2;
            updadd(s * 2, l, min(r, m), lb, m, v);
            updadd(s * 2 + 1, max(l, m + 1), r, m + 1, rb, v);
            pull(s);
        }
    }
    void updadd(int l, int r, int v) { updadd(1, l, r, 0, n - 1, v); }
    ll query(int s, int l, int r, int lb, int rb) {
        if(l > r) return 0;
        if (l == lb && rb == r)
            return tr[s];
        push(s, lb, rb);
        int m = (lb + rb) / 2;
        ll lr = query(s * 2, l, min(r, m), lb, m);
        ll rr = query(s * 2 + 1, max(l, m + 1), r, m + 1, rb);
        return lr + rr;
    }
    ll query(int l, int r) { return query(1, l, r, 0, n - 1); }
};

// sparse
template<ll SZ> struct node {
    ll val = 0;
    ll lzadd = 0, lzset = 0;
    node *left, *right;
    node() { left = right = NULL; }
    void push(ll l, ll m, ll r) {
        if(!left) left = new node();
        if(!right) right = new node();
        if(lzset != 0) {
            left->val = (m - l + 1) * lzset;
            right->val = (r - m) * lzset;
            left->lzset = right->lzset = lzset;
            left->lzadd = right->lzadd= 0;
            lzset = 0;
        }
        else {
            left->val += (m - l + 1) * lzadd;
            if(left->lzset == 0) left->lzadd += lzadd;
            else left->lzset += lzadd, left->lzadd = 0;
            right->val += (r - m) * lzadd;
            if(right->lzset == 0) right->lzadd += lzadd;
            else right->lzset += lzadd, right->lzadd = 0;
            lzadd = 0;
        }
    }
    void updset(ll iv, ll l, ll r, ll lb = 0, ll rb = SZ) {
        if(l > r) return;
        if(l == lb && r == rb) { 
            val = iv * (rb - lb + 1); 
            lzset = iv; 
            lzadd = 0;
            return; 
        }
        ll m = (lb + rb) / 2;
        push(lb, m, rb);
        left->updset(iv, l, min(r, m), lb, m);
        right->updset(iv, max(l, m + 1), r, m + 1, rb);
        val = left->val + right->val;
    }
    void updadd(ll av, ll l, ll r, ll lb = 0, ll rb = SZ) {
        if(l > r) return;
        if(l == lb && r == rb) { 
            val += av * (rb - lb + 1);
            if(lzset == 0) lzadd += av;
            else lzset += av;
            return; 
        }
        ll m = (lb + rb) / 2;
        push(lb, m, rb);
        left->updadd(av, l, min(r, m), lb, m);
        right->updadd(av, max(l, m + 1), r, m + 1, rb);
        val = left->val + right->val;
    }
    ll query(ll l, ll r, ll lb = 0, ll rb = SZ) {
        if(l > r) return 0;
        if(l == lb && r == rb) return val;
        ll m = (lb + rb) / 2;
        push(lb, m, rb);
        ll re = left->query(l, min(r, m), lb, m) + right->query(max(l, m + 1), r, m + 1, rb);
        //cout << this << " " << lb << " " << rb << " " << re << endl;
        return re;
    }
};


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, q; cin >> n >> q;
    //node<200000>* segt = new node<200000>();
    RURQ segt(n);
    for(int i = 1; i <= n; i++) {
        int a; cin >> a;
        //segt->updset(a, i, i);
        segt.updset(i - 1, i - 1, a);
    }
    for(int i = 0; i < q; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 3) {
            cout << segt.query(a - 1, b - 1) << endl;
            //cout << segt->query(a, b) << endl;
        } else {
            int x; cin >> x;
            //if(t == 1) segt->updadd(x, a, b);
            //else segt->updset(x, a, b);
            if(t == 1) segt.updadd(a - 1, b - 1, x);
            else segt.updset(a - 1, b - 1, x);
        }
    }
}