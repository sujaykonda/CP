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

ll lcm(ll x, ll y) {
    if(x == -1 || y == -1) return -1;
    ll m = (x / __gcd(x, y)) * y;
    if(m > 1e14) return -1;
    else return m;
}

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
// sparse table
template<class T, T comb(T, T)>
struct SPT : vector<vector<T>> {
    SPT(vector<T>& v) : vector<vector<T>>(lg(v.size()) + 1, vector<T>(v.size())) {
        (*this)[0] = v;
        for (int i = 0; i < lg(v.size()); i++)
            for (int j = 0; j <= v.size() - (1 << (i + 1)); j++)
                (*this)[i + 1][j] = comb((*this)[i][j], (*this)[i][j + (1 << i)]);
    }
    T query(int L, int R) {
        int i = lg(R - L + 1);
        return comb((*this)[i][L], (*this)[i][R - (1 << i) + 1]);
    }
};

void testcase() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++)
        cin >> a[i] >> b[i];

    // sparse table
    SPT<ll, lcm> st(b);

    vector<ll> ab(n);
    for(int i = 0; i < n; i++)
        ab[i] = a[i] * b[i];
    SPT<ll, __gcd> st2(ab);
    
    vector<int> dp(n + 1, n);
    dp[0] = 0;
    int j = 0;
    for(int i = 0; i < n; i++) {
        while(st.query(j, i) == -1 || st2.query(j, i) % st.query(j, i) != 0) j++;
        dp[i + 1] = 1 + dp[j];
    }
    cout << dp[n] << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}