//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

// basic (VERY BUGGY IDK HOW THIS WORKS)
struct SegT {
    int n;
    vector<int> tr;
    SegT(int n) : n(n), tr(2 * n + 1, n) {}
    void upd(int k, int v) {
        k += n, tr[k] = v;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = min(tr[2 * k], tr[2 * k + 1]);
    }
    int query(int a, int b) {
        a += n, b += n;
        int r = n;
        while(a <= b) {
            if(a % 2 == 1) r = min(tr[a++], r);
            if(b % 2 == 0) r = min(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> a(n); cin >> a;
    
    vector<vector<pair<int, int>>> queries(n);
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--, r--;
        queries[l].pb({r, i});
    }
    vector<int> ans(q);
    SegT segt(n), dp(n);
    for(int i = n - 1; i >= 0; i--) {
        a[i]--; segt.upd(a[i], i);
        int cur = segt.query(a[i] + 1, n - 1);
        while(cur != n) {
            if(dp.tr[n + cur] > a[cur] - a[i])
                dp.upd(cur, a[cur] - a[i]);
            cur = segt.query(a[i] + 1, (a[cur] + a[i] - 1) / 2);
        }
        cur = segt.query(0, a[i] - 1);
        while(cur != n) {
            if(dp.tr[n + cur] > a[i] - a[cur])
                dp.upd(cur, a[i] - a[cur]);
            cur = segt.query((a[cur] + a[i]) / 2 + 1, a[i] - 1);
        }
        for(auto [u, v] : queries[i])
            ans[v] = dp.query(i + 1, u);
    }
    for(int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}