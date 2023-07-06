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
    int suc; 
    if(n == 2) {
        cout << "! 1 2 2 1" << endl; 
        cin >> suc; return; 
    }
    cout << "+ " << n + 1 << endl;
    cin >> suc;
    cout << "+ " << n + 2 << endl;
    cin >> suc;
    // graph now looks like 1 - n - 2 - n-1 - 3 - n-2 - 4...
    vector<int> o(n + 1);
    for(int i = 1; i <= n; i++)
        o[i] = (i % 2 == 1) ? (1 + i / 2) : (n - i / 2 + 1);
    // make n - 1 queries of the form 1 - 2, 1 - 3, 1 - 4...
    int best = 1, bdist = 0;
    for(int i = 2; i <= n; i++) {
        cout << "? 1 " << i << endl;
        cout.flush();
        int res; cin >> res;
        if(bdist < res) bdist = res, best = i;
    }
    // make n - 1 queries of the form best - 1, best - 2, best - 3, best - 4...
    vector<int> dist(n + 1);
    for(int i = 1; i <= n; i++) {
        if(i == best) {
            dist[i] = 0; continue;
        }
        cout << "? " << best << " " << i << endl;
        cout.flush();
        cin >> dist[i];
    }
    cout << "! ";
    for(int i = 1; i <= n; i++)
        cout << o[dist[i] + 1] << " ";
    for(int i = 1; i <= n; i++)
        cout << o[n - dist[i]] << " ";
    cout << endl;
    cin >> suc;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}