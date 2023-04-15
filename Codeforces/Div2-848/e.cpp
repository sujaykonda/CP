#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

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

// xor basis
template<int SZ> struct XorBasis {
    array<int, SZ> basis{};
    void add(int mask) {
        for(int i = SZ - 1; i >= 0; i--) {
            if(getbit(mask, i)) {
                if(!basis[i]) { basis[i] = mask; return; }
                mask ^= basis[i];
            }
        }
    }
};

struct SRQ {
    vector<int> v;
    vector<vector<XorBasis<31>>> tab;
    SRQ(vector<int>& v) : v(v), tab(lg(v.size()) + 1, vector<XorBasis<31>>(v.size())) {
        for(int k = 1; k <= v.size(); k++) {
            // cool trick!
            int rad = 1, i = 0; while(k % (2 * rad) == 0) rad *= 2, i++;
            tab[i][k - 1] = T(v[k - 1]);
            for(int j = k - 2; j >= k - rad; j--)
                tab[i][j] = comb(v[j], tab[i][j + 1]);
            if(k < v.size()) tab[i][k] = v[k];
            for(int j = k + 1; j < v.size() && j < k + rad; j++)
                tab[i][j] = comb(tab[i][j - 1], v[j]); 
        }
    }
    T query(int L, int R) {
        if(L == R) return v[L]; int i = lg(R ^ L);
        return comb(tab[i][L], tab[i][R]);
    }
};




void testcase() {
    int n; cin >> n;
    vector<int> a(n); cin >> a;
    
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) testcase();

}