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
    if(n % 2 == 0) { cout << -1 << endl; return; }
    vector<int> a;
    while(n > 1) {
        if((n + 1) / 2 % 2 == 1) 
            a.push_back(1), n = (n + 1) / 2;
        else
            a.push_back(2), n = (n - 1) / 2;
    }
    cout << a.size() << endl;
    for(int i = a.size() - 1; i >= 0; i--)
        cout << a[i] << " ";
    cout << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}
