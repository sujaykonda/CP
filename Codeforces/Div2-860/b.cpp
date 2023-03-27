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

array<int, 50001> cnt;
void testcase() {
    int m; cin >> m;
    vector<vector<int>> a(m, vector<int>());
    for(int i = 0; i < m; i++) {
        int n; cin >> n;
        a[i].resize(n);
        for(int j = 0; j < n; j++)
            cin >> a[i][j], cnt[a[i][j]]++;
    }
    vector<int> p(m);
    bool good = true;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < a[i].size(); j++)
            cnt[a[i][j]]--;
        for(int j = 0; j < a[i].size(); j++)
            if(cnt[a[i][j]] == 0)
                p[i] = a[i][j];
        if(p[i] == 0)
            good = false;
    }
    if(good) {
        for(int i = 0; i < p.size(); i++)
            cout << p[i] << " ";
        cout << endl;
    } else {
        cout << "-1" << endl;
    }
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}