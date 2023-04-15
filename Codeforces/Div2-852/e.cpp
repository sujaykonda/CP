#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int& a) { return to_string(a); } string str(ll& a) { return to_string(a); }
string str(char& a) { return to_string(a); } string str(_Bit_reference& a) { return to_string(a); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

int main() {
    int n; cin >> n;
    vector<int> a(n); cin >> a;
    sort(a.begin(), a.end());
    // maximizing sections
    vector<int> mx(n + 1), dp(n + 1);
    mx[0] = 0, dp[0] = 0;
    for(int i = 1; i <= n; i++) 
        dp[i] = ((i >= a[i - 1]) ? mx[i - a[i - 1]] : i - a[i - 1]) + 1, mx[i] = max(mx[i - 1], dp[i]);
    vector<int> mn(n + 1);
    mn[0] = n;
    for(int i = 1; i <= n; i++) mn[i] = min(mn[i - 1], n - i + dp[i]);
    reverse(mn.begin(), mn.end());
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int k; cin >> k;
        int j = lower_bound(mn.begin(), mn.end(), k) - mn.begin();
        cout << n - j << endl;
    }
}