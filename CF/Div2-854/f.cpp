#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "T" : "F"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T& a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

void testcase() {
    int n, b, k1, k2;
    cin >> n >> b >> k1 >> k2;
    vector<int> a(n); cin >> a;
    sort(a.begin(), a.end(), greater<int>());
    ll mincost = 1e18;
    for(int bo = 0; bo <= min(k1, k2); bo++) {
        ll cost = 0;
        for(int i = 0; i < bo; i++)
            cost += max((a[i] + 1) / 2 - b, 0);
        if(k1 + k2 - bo > n) continue;
        priority_queue<int> gains;
        for(int i = bo; i < k1 + k2 - bo; i++)
            cost += max(0, a[i] - b), gains.push(max(0, a[i] - b) - (a[i] + 1) / 2);
        for(int i = k1 + k2 - bo; i < n; i++) cost += a[i];
        for(int i = 0; i < k1 - bo; i++)
            cost -= gains.top(), gains.pop();
        mincost = min(cost, mincost);
    }
    cout << mincost << endl;
}

int main() {
    int t; cin >> t;
    while(t--) testcase();
}