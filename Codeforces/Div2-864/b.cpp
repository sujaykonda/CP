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
    int n, k; cin >> n >> k;
    vector<vector<int>> grid(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> grid[i][j];

    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(grid[i][j] != grid[n - i - 1][n - j - 1]) cnt++;
    k -= cnt / 2;
    if(k < 0) cout << "NO" << endl;
    else if(k % 2 == 0 || n % 2 == 1) cout << "YES" << endl;
    else cout << "NO" << endl;
} 

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}