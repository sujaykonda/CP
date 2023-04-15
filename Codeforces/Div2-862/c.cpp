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
    int n, m; cin >> n >> m;
    vector<ll> k(n);
    for(int i = 0; i < n; i++) cin >> k[i];
    sort(k.begin(), k.end());
    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        auto it = lower_bound(k.begin(), k.end(), b);
        if(it != k.end()) it++;
        pair<ll, ll> bestline = {2e9, 0};
        if(it != k.end())
            bestline = min(bestline, {llabs(b - *it), *it});
        it--;
        bestline = min(bestline, {llabs(b - *it), *it});
        if(it != k.begin()) {
            it--;
            bestline = min(bestline, {llabs(b - *it), *it});
        }
        if(bestline.first * bestline.first < 4 * a * c)
            cout << "YES" << "\n" << bestline.second << endl;
        else
            cout << "NO" << endl; 
    }
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}