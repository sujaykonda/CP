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

ll sqrt(ll x)
{
    ll hi = 1e9, lo = 0;
    while (hi > lo)
    {
        ll mid = (hi + lo + 1) / 2;
        if (mid * mid < x)
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}


int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        ll n;
        cin >> n;
        cout << (ll)sqrt(n) << endl;
    }
}