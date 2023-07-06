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

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        string s;
        cin >> s;
        array<int, 10> cnt{};
        for(int i = 0; i < s.length(); i++)
            cnt[s[i] - '0']++;
        int mxcnt = 0;
        for(int i = 0; i < 10; i++)
            mxcnt = max(mxcnt, cnt[i]);
        if(mxcnt == 4) cout << -1 << endl;
        else if(mxcnt == 3) cout << 6 << endl;
        else cout << 4 << endl;
    }
}