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

inline ll calc_seg(ll sz) {
    return (sz * (sz + 1ll)) / 2ll;
}

int main() {
    ll n; cin >> n;
    vector<ll> p(n), q(n), rp(n + 1), rq(n + 1);
    cin >> p >> q;
    for(int i = 0; i < n; i++) rp[p[i]] = i, rq[q[i]] = i;
    
    ll ans = 1 + calc_seg(min(rp[1], rq[1])) + calc_seg(max(0ll, llabs(rp[1] - rq[1]) - 1ll)) + calc_seg(n - 1 - max(rp[1], rq[1]));
    ll l = n - 1, r = 0;
    for(int i = 1; i < n; i++) {
        l = min({l, rp[i], rq[i]});
        r = max({r, rp[i], rq[i]});
        ll l2 = min(rp[i + 1], rq[i + 1]), r2 = max(rp[i + 1], rq[i + 1]);
        if(r < l2) {
            ans += (l + 1ll) * (l2 - r);
        }
        if(r2 < l) {
            ans += (l - r2) * (n - r);
        } 
        if(l2 < l && r < r2) {
            ans += (l - l2) * (r2 - r);
        }
    }
    cout << ans << endl;
}