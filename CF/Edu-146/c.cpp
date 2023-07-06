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
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    vector<pair<int, int>> r(n);
    for(int i = 0; i < n; i++)
        cin >> r[i].first, r[i].second = i + 1;
    sort(r.begin(), r.end());
    reverse(r.begin(), r.end());
    vector<int> a, b;
    int t1 = 0, t2 = 0;
    for(auto &[u, v] : r) {
        if(t1 + s1 < t2 + s2) {
            a.push_back(v);
            t1 += s1;
        } else {
            b.push_back(v);
            t2 += s2;
        }
    }
    cout << a.size() << " ";
    for(int i : a) cout << i << " ";
    cout << endl;
    cout << b.size() << " ";
    for(int i : b) cout << i << " ";
    cout << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}