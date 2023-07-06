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
    string a, b; cin >> a >> b;
    if(a[0] == b[0]) {
        cout << "YES\n" << a[0] << "*\n";
    } else if(a.back() == b.back()) {
        cout << "YES\n*" << a.back() << "\n";
    } else {
        for(int i = 0; i < a.size() - 1; i++) {
            for(int j = 0; j < b.size() - 1; j++) {
                if(a.substr(i, 2) == b.substr(j, 2)) {
                    cout << "YES\n*" << a.substr(i, 2) << "*\n";
                    return;
                }
            }
        }
        cout << "NO" << endl;
    }
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}