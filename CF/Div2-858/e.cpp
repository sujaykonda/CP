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
 
ll n, q;
vector<int> p;
vector<ll> a;
vector<vector<ll>> dp;
vector<int> depth, cnt, hsh;
 
ll getdp(int x, int y) {
    if(x == 0 && y == 0) return 0;
    if(cnt[depth[y]] * cnt[depth[y]] <= n) {
        if(!dp[x][hsh[y]])
            dp[x][hsh[y]] = a[x] * a[y] + getdp(p[x], p[y]);
        return dp[x][hsh[y]];
    }
    return a[x] * a[y] + getdp(p[x], p[y]);
}
 
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> q;
    p.resize(n + 1), a.resize(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 2; i <= n; i++) cin >> p[i];
    
    depth.resize(n + 1), cnt.resize(n + 1), hsh.resize(n + 1);
    for(int i = 1; i <= n; i++) depth[i] = 1 + depth[p[i]], hsh[i] = cnt[depth[i]]++;
 
    dp.resize(n + 1);
    for(int i = 1; i <= n; i++) if(cnt[depth[i]] * cnt[depth[i]] <= n) dp[i].resize(cnt[depth[i]]);
    for(int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        cout << getdp(x, y) << endl;
    }
}