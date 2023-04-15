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
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }

void testcase() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    vector<int> dp(n + 1, -1);
    dp[n] = 0;
    for(int i = n - 1; i >= 0; i--)
        if(i + a[i] + 1 <= n && dp[i + a[i] + 1] >= 0) 
            dp[i] = dp[i + a[i] + 1] + 1;

    vector<int> dp2(n + 1);
    int mxln = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(dp[i] >= 0) mxln = max(mxln, dp[i]);
        else {
            dp2[i] = mxln;
            if(i + a[i] + 1 <= n)
                dp2[i] = max(dp2[i], dp2[i + a[i] + 1] + 1);
        }
    }
    
    for(int i = 0; i < n - 1; i++) {
        if(a[i] == dp[i + 1]) cout << "0 ";
        else if(dp[i + 1] >= 0) cout << "1 ";
        else if(dp2[i + 1] + 1 >= a[i]) cout << "1 ";
        else cout << "2 ";
    }
    cout << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}