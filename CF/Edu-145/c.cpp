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

void solve(int n, int k, vector<int>& ans) {
    if(n == 0 && k == 0) return;
    if(k >= n) {
        solve(n - 1, k - n, ans);
        ans.push_back(1000);
    } else {
        for(int i = 0; i < k - 1; i++) {
            ans.push_back(-1);
        }
        if(k > 0) {
            ans.push_back(30);
            ans.push_back(-60);
        }
        while(ans.size() < n) ans.push_back(-1);
    }
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        vector<int> ans;
        solve(n, k, ans);
        for(int i = 0; i < n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}