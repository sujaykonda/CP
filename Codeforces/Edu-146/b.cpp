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
    int a, b; cin >> a >> b;
    int best = a + b;
    for(int i = 1; i * i <= max(a, b); i++) {
        best = min(best, (i - 1) + (a + i - 1) / i + (b + i - 1) / i);
        int o = (max(a, b) + i - 1) / i;
        //cout << o << endl;
        best = min(best, (o - 1) + (a + o - 1) / o + (b + o - 1) / o);
    }
    cout << best << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}