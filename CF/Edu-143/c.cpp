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
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) p[i + 1] = p[i] + b[i];
    vector<ll> d(n + 2);
    vector<ll> e(n);
    for(int i = 0; i < n; i++) {
        ll lo = i - 1, hi = n;
        while (hi > lo)
        {
            ll mid = (hi + lo + 1) / 2;
            if (p[mid] - p[i] <= a[i])
                lo = mid;
            else
                hi = mid - 1;
        }
        if(lo < n)
            e[lo] += a[i] - (p[lo] - p[i]);
        d[i]++, d[lo]--;
    }
    ll s = 0;
    for(int i = 0; i < n; i++) {
        s += d[i];
        cout << b[i] * s + e[i] << " ";
    }
    cout << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}