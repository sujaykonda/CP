#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; s.pop_back(), s.pop_back(), s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; } 

string cmpstr;

void testcase() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    for(int i = 0; i < 20; i++) {
        if(cmpstr.substr(i, k) == s) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}

int main() {
    cmpstr = "";
    for(int n = 0; n < 100; n++) {
        if(n % 3 == 0) cmpstr += "F";
        if(n % 5 == 0) cmpstr += "B";
    }
    //cout << cmpstr << endl;
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}