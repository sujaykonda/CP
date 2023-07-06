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

void testcase() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int l = 0, r = n - 1;
    int mn = 1, mx = n;
    while(l < r) {
        if(a[l] == mn) {
            l++, mn++; continue;
        }
        if(a[r] == mn) {
            r--, mn++; continue;
        }
        if(a[l] == mx) {
            l++, mx--; continue;
        }
        if(a[r] == mx) {
            r--, mx--; continue;
        }
        break;
    }
    if(l == r) cout << -1 << endl;
    else cout << l + 1 << " " << r + 1 << endl;
}

int main() {
    int t; cin >> t;
    while(t--) testcase();
}