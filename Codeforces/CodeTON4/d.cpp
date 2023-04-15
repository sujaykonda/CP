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
template<class T> inline T ceildiv(T a, T b) { return a / b + (a % b != 0); }

void testcase() {
    int q; cin >> q;
    pair<ll, ll> range = {1, 1e18};
    vector<ll> ans(q);
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll a, b, n; cin >> a >> b >> n;
            pair<ll, ll> nrange;
            if(n == 1) {
                nrange = {1, a};
            } else {
                nrange = {a + (n - 2) * (a - b) + 1, (n - 1) * (a - b) + a};
            }
            if(nrange.second < range.first || range.second < nrange.first) ans[i] = 0;
            else range.first = max(range.first, nrange.first), range.second = min(range.second, nrange.second), ans[i] = 1;
        } else {
            ll a, b; cin >> a >> b;
            ll leftans = (range.first > a ? ceildiv((range.first - a), (a - b)) : 0) + 1;
            ll rightans = (range.second > a ? ceildiv((range.second - a), (a - b)) : 0) + 1;
            if(leftans == rightans) ans[i] = leftans;
            else ans[i] = -1;
        }
    }
    for(int i = 0; i < q; i++)
        cout << ans[i] << " ";
    cout << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}