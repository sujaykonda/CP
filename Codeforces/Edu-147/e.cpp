#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
// debug tools
string str(char c) { return string(1, c); } string str(_Bit_reference b) { return b ? "T" : "F"; }
string str(int x) { return to_string(x); } string str(ll x) { return to_string(x); }
template<class T> string str(T a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

void dfs(int s, vector<int>& sz, vector<vector<int>>& ch) {
    for(int u : ch[s])
        dfs(u, sz, ch), sz[s] += sz[u];
}
void testcase() {
    int k; cin >> k;
    string s; cin >> s; int n = s.size() / 2;
    vector<vector<int>> ch(n + 1);

    // make graph
    {
        stack<int> st; st.push(0);
        int i = 1;
        for(char c : s) {
            if(c == '(') ch[st.top()].pb(i), st.push(i++);
            else st.pop();
        }
    }

    vector<int> sz(n + 1, 1);
    dfs(0, sz, ch);

    vector<vector<int>> so(n + 1);
    for(int i = 1; i < ch.size(); i++) so[sz[i]].pb(i);
    
    int left = n - k;
    ll cost = 0;
    for(int i = 0; i <= ch.size(); i++) {
        if(left <= 0) break;
        for(int j : so[i]) {
            if(left <= 0) break;
            cost += i - 1; left--;
        }
    }
    cout << cost << nl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) testcase();
}