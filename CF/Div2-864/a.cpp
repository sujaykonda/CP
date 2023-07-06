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
    int x1, y1, x2, y2;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    int mnst = 4;
    if(x1 == 1 || x1 == n) mnst--;
    if(y1 == 1 || y1 == m) mnst--;
    int mnen = 4;
    if(x2 == 1 || x2 == n) mnen--;
    if(y2 == 1 || y2 == m) mnen--;
    cout << min(mnst, mnen) << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++)
        testcase();
}