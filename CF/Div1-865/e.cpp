#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
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

const int MOD = 998244353;
const int MX = 2e6 + 1;
array<int, MX> lpf;

void lpfsieve()
{
    for (ll i = 1; i < MX; i++)
        lpf[i] = i;
    for (ll i = 2; i < MX; i++)
        if (lpf[i] == i)
            for (ll j = i; j < MX; j += i)
                lpf[j] = i;
}

vector<pair<ll, ll>> pf(int x)
{
    vector<pair<ll, ll>> f;
    while (x != 1)
    {
        if (f.size() > 0 && f.back().first == lpf[x])
            f.back().second++;
        else
            f.push_back({lpf[x], 1});
        x /= lpf[x];
    }
    return f;
}

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    lpfsieve();
    int n; cin >> n;
    vector<string> s(n); cin >> s;
    for(int i = 0; i < n; i++) {
        int sz = s[i].size();
        while(sz > 1) {
            bool good = true;
            int split = s[i].size() / lpf[sz];
            for(int j = split; j < s[i].size(); j++) {
                if(s[i][j % split] != s[i][j])
                    good = false;
            }
            if(good) s[i] = s[i].substr(0, split);
            sz /= lpf[sz];
        }
    }
    for(int i = 0; i < n; i++) {
        if(s[i] == "1") {
            n = i, s.resize(n);
            break;
        }
    }
    if(n == 0) {
        cout << 2 << endl;
        return 0;
    }
    vector<ll> in(n), out(n), val(n);
    for(int i = 0; i < n; i++) {
        int j = 0;
        do {
            if(s[i][j] == '1') j = (j + 1) % s[i].size(), val[i]++;
            else {
                j = (j + 1) % s[i].size();
                out[i]++;
                while(s[i][j] == '1') j = (j + 1) % s[i].size(), out[i]++, val[i]--;
                j = (j + 1) % s[i].size();
            }
            in[i]++;
        } while(j != 0);
    }
    array<ll, MX> mpf{};
    for(int i = n - 1; i > 0; i--) {
        for(auto [u, v] : pf(in[i])) mpf[u] += v;
        for(auto [u, v] : pf(out[i - 1])) mpf[u] = max(mpf[u] - v, 0ll);
    }
    
    ll lout = in[0];
    for(int i = 1; i < MX; i++)
        lout = (lout * fe(i, mpf[i], MOD)) % MOD;

    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ll inv = minv(in[i], MOD);
        ans = (ans + ((i + 1) * val[i] % MOD) * (lout * inv % MOD)) % MOD;
        lout = out[i] * (lout * inv % MOD) % MOD;
    }
    ans = (ans + lout * (n + 1)) % MOD;
    cout << (2 * ans) % MOD << endl;
}
