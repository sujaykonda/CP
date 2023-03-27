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

ll lcm(ll x, ll y) {
    if(x == -1 || y == -1) return -1;
    ll m = (x / __gcd(x, y)) * y;
    if(m > 1e9) return -1;
    else return m;
}

int query(int L, int R, vector<vector<ll>>& st)
{
    if (L > R) swap(L, R);
    int i = lg(R - L + 1);
    return lcm(st[i][L], st[i][R - (1 << i) + 1]);
}

void testcase() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++)
        cin >> a[i] >> b[i];

    // sparse table
    
    vector<vector<ll>> st(lg(n) + 1, vector<ll>(n));
    for(int i = 0; i < n; i++)
        st[0][i] = b[i];
    //cout << "st building" << endl;
    for (int i = 0; i < lg(n); i++)
        for (int j = 0; j < n - (1 << i); j++)
            st[i + 1][j] = lcm(st[i][j], st[i][j + (1 << i)]);
    //cout << "st building" << endl;
    cout << strnl(st) << endl;
    
    vector<int> dp(n + 1, n);
    dp[0] = 0;
    int j = 0;
    for(int i = 0; i < n; i++) {
        while(query(j, i, st) == -1 || a[i] % (query(j, i, st) / b[i]) != 0) j++;
        cout << i << " " << j << endl;
        dp[i + 1] = 1 + dp[j];
    }
    cout << dp[n] << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}