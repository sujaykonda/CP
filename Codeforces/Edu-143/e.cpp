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
    ll n; cin >> n;
    vector<ll> h(n + 2), p(n + 2);
    for(int i = 1; i <= n; i++)
        cin >> h[i], p[i] = p[i - 1] + h[i];
    h[0] = -1e6, h[n + 1] = -1e6;
    vector<ll> ldp(n + 2), rdp(n + 2);
    stack<int> s;
    s.push(0);
    for(int i = 1; i <= n; i++) {
        while(h[s.top()] - s.top() > h[i] - i) s.pop();
        ll j = s.top();
        ll len = min(h[i], i - j);
        ldp[i] = p[i] - p[j] - ((2 * h[i] - len + 1) * len) / 2 + ldp[j];
        s.push(i);
    }
    while(!s.empty()) s.pop();
    s.push(n + 1);
    for(int i = n; i >= 1; i--) {
        while(h[s.top()] + s.top() > h[i] + i) s.pop();
        ll j = s.top();
        ll len = min(h[i], j - i);
        rdp[i] = p[j - 1] - p[i - 1] - ((2 * h[i] - len + 1) * len) / 2 + rdp[j];
        s.push(i);
    }
    ll best = n * 1e6;
    for(int i = 1; i <= n; i++) best = min(best, h[i] + ldp[i] + rdp[i]);
    cout << best << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++)
        testcase();
}