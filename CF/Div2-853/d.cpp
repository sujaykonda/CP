#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "T" : "F"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T& a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

bool check_zero(string& s) {
    for(char c : s) if(c != '0') return false;
    return true;
}

string apply(int k, string a) {
    string n = a;
    for(int i = 0; i < a.size(); i++) {
        if(i - k >= 0 && i - k < a.size()) {
            n[i - k] = a[i] == n[i - k] ? '0' : '1';
        }
    }
    return n;
}

void testcase() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    if(a == b) { cout << 0 << '\n'; return; }
    if(check_zero(a) || check_zero(b)) { cout << -1 << '\n'; return; }
    // make lowest bit the same
    int lba = -1, lbb = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] == '1' && lba == -1) lba = i;
        if(b[i] == '1' && lbb == -1) lbb = i; 
    }
    vector<int> opr;
    if(lba != lbb) {
        if(a[lbb] != b[lbb]) {
            opr.pb(lba - lbb);
            a = apply(opr.back(), a);
        }
        if(lba < lbb) {
            int hba = -1;
            for(int i = n - 1; i >= 0; i--) 
                if(a[i] == '1' && hba == -1) 
                    hba = i;
            for(int i = lbb - 1; i >= 0; i--) {
                if(a[i] != b[i]) {
                    opr.pb(hba - i);
                    a = apply(opr.back(), a);
                }
            }
        }
    }
    for(int i = lbb + 1; i < n; i++) {
        if(a[i] != b[i]) {
            opr.pb(lbb - i);
            a = apply(opr.back(), a);
        }
    }
    cout << opr.size() << endl;
    for(int o : opr) cout << o << " ";
    cout << endl;
}

int main() {
    int t; cin >> t;
    while(t--) testcase();
}