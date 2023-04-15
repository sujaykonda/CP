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
    int n, m; cin >> n >> m;
    cout << "? 1 1\n";
    cout.flush();
    int dist; cin >> dist;
    cout << "? " << min(n, dist + 1) << " " << min(m, dist + 1) << endl;
    cout.flush();
    int dist2; cin >> dist2;
    cout << "? " << max(1, min(n, dist + 1) - dist2) << " " << min(m, dist + 1) << endl;
    int fin; cin >> fin;
    if(fin == 0) cout << "! " << max(1, min(n, dist + 1) - dist2) << " " << min(m, dist + 1) << endl;
    else cout << "! " <<  min(n, dist + 1) << " " << max(1, min(m, dist + 1) - dist2) << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}