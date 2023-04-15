#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }


void testcase() {
    int n; cin >> n;
    string s; cin >> s;
    for(char c = 'a'; c <= 'z'; c++) {
        for(int i = n - 1; i >= 0; i--) {
            if(s[i] == c) {
                cout << c;
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;
                    cout << s[j];
                }
                cout << endl;
                return;
            }
        }
    }
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}