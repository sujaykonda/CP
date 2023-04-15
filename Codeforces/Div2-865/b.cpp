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
    vector<vector<int>> a(2, vector<int>(n));
    int even = 2 * n, odd = 2;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0)
            a[0][i] = even, even -= 2;
        else
            a[0][i] = odd, odd += 2;
    }

    odd = 2 * n - 1, even = 1;
    for(int i = n - 1; i >= 0; i--) {
        if(i % 2 == 0)
            a[1][i] = even, even += 2;
        else
            a[1][i] = odd, odd -= 2;
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}