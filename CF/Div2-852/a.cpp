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
    ll a, b, n, m;
    cin >> a >> b;
    cin >> n >> m;
    if(b > a) {
        cout << n / (m + 1) * m * a + (n % (m + 1)) * a << endl;
    } else {
        cout << min(n / (m + 1) * m * a + (n % (m + 1)) * b, n * b) << endl;
    }
}

int main() {
    int t; cin >> t;
    while(t--) testcase();    
}