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

const ll MOD = 998244353;
void testcase() {
    int n; cin >> n;
    ll last = 0;
    ll mult = 1;
    for(int i = 1; i < n; i++) {
        int a; cin >> a;
        last = (last * i) % MOD;
        if(a == 0) last = (last + mult) % MOD;
        cout << last << " ";
        mult = (mult * (i - a)) % MOD;
    }
    cout << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++)
        testcase();
}