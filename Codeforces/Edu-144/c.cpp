#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

void testcase() {
    int l, r; cin >> l >> r;
    int mx = 1;
    while((1 << mx) * l <= r) mx++;
    ll ans = r / (1 << (mx - 1)) - l + 1;
    if(mx > 1 && r / (1 << (mx - 2)) / 3 >= l)
        ans += (mx - 1) * (r / (1 << (mx - 2)) / 3 - l + 1);
    cout << mx << " " << ans << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++)
        testcase();
}