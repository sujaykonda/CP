#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
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

int n; 
vector<ll> a, b;
bool solve(int h, int w) {
    set<pair<ll, int>> sa, sb;
    for(int i = 0; i < n; i++)
        sa.insert({a[i], i}), sb.insert({b[i], i});
    int cutcnt = 0;
    bool hor = true;
    while(cutcnt < n - 1) {
        if(hor) {
            if((*sa.rbegin()).first != h) return false;
            while(sa.size() > 1 && (*sa.rbegin()).first == h) {
                w -= b[(*sa.rbegin()).second];
                cutcnt++;
                sb.erase({b[(*sa.rbegin()).second], (*sa.rbegin()).second});
                sa.erase(*sa.rbegin());
            }
            if(w < 0) return false;
        } else {
            if((*sb.rbegin()).first != w) return false;
            while(sb.size() > 1 && (*sb.rbegin()).first == w) {
                h -= a[(*sb.rbegin()).second];
                cutcnt++;
                sa.erase({a[(*sb.rbegin()).second], (*sb.rbegin()).second});
                sb.erase(*sb.rbegin());
            }
            if(h < 0) return false;
        }
        hor = !hor;
    }
    return h == a[(*sa.begin()).second] && w == b[(*sa.begin()).second];
}

void testcase() {
    cin >> n;
    a = b = vector<ll>(n);
    ll area = 0;
    ll mxa = 0, mxb = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        mxa = max(mxa, a[i]);
        mxb = max(mxb, b[i]);
        area += (a[i] * b[i]);
    }
    if(n == 1) {
        cout << 1 << endl << a[0] << " " << b[0] << endl;
        return;
    }
    set<pair<ll, ll>> poss;
    if(area % mxa == 0 && solve(mxa, area / mxa))
        poss.insert({mxa, area / mxa});
    for(int i = 0; i < n; i++)
        swap(a[i], b[i]);
    if(area % mxb == 0 && solve(mxb, area / mxb))
        poss.insert({area / mxb, mxb});
    cout << poss.size() << endl;
    for(auto [h, w] : poss)
        cout << h << " " << w << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) testcase();
}