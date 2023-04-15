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

template <int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
    mint& operator+=(mint o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int((long long) v * o.v % MOD); return *this; }
    friend mint pow(mint a, long long p) { assert(p >= 0); return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1); }
    friend mint inv(mint a) { return pow(a, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend string str(mint a) { return to_string(a.v); }
    friend bool operator<(mint a, mint b) { return a.v < b.v; }
};

const int MOD = 1e9 + 7;
void testcase() {
    int N; cin >> N;
    vector<int> h(N);
    for(int i = 0; i < N; i++)
        cin >> h[i];

    int O = 0, E = 0;
    vector<int> id(N);
    for(int i = 0; i < N; i++)
        id[i] = h[i] % 2 ? ++O : ++E;

    array<vector<int>, 2> restr = {vector<int>(E + 1), vector<int>(O + 1)};
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            if(h[i] % 2 != h[j] % 2 && abs(h[i] - h[j]) >= 2)
                restr[h[j] % 2][id[j]] = max(restr[h[j] % 2][id[j]], id[i]);
        }
    }
    vector<vector<mint<MOD>>> dp(O + 1, vector<mint<MOD>>(E + 1));
    dp[0][0] = 1;
    for(int i = 0; i <= O; i++) {
        for(int j = 0; j <= E; j++) {
            if(i > 0 && restr[1][i] <= j)
                dp[i][j] += dp[i - 1][j];
            if(j > 0 && restr[0][j] <= i)
                dp[i][j] += dp[i][j - 1];
        }
    }
    cout << str(dp[O][E]) << endl;
}

int main() {
    int T; cin >> T;
    for(int i = 0; i < T; i++) testcase();
}