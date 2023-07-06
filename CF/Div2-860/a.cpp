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

void testcase() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    int amx = a[0], bmx = b[0];
    for(int i = 0; i < n; i++)
        amx = max(amx, a[i]), bmx = max(bmx, b[i]);
    if(a[n - 1] == amx && b[n - 1] == bmx) cout << "Yes" << endl;
    else if(a[n - 1] != amx && b[n - 1] != bmx) {
        cout << "No" << endl;
    }
    else if(a[n - 1] != amx) {
        for(int i = 0; i < n; i++) {
            if(a[i] > a[n - 1]) swap(a[i], b[i]);
        }
        int namx = a[0];
        for(int i = 0; i < n; i++)
            namx = max(namx, a[i]);
        int nbmx = b[0];
        for(int i = 0; i < n; i++)
            nbmx = max(nbmx, b[i]);
        if(nbmx == b[n - 1] && namx == a[n - 1])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    else if(b[n - 1] != bmx) {
        for(int i = 0; i < n; i++) {
            if(b[i] > b[n - 1]) swap(b[i], a[i]);
        }
        int namx = a[0];
        for(int i = 0; i < n; i++)
            namx = max(namx, a[i]);
        int nbmx = b[0];
        for(int i = 0; i < n; i++)
            nbmx = max(nbmx, b[i]);
        if(namx == a[n - 1] && nbmx == b[n - 1])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}