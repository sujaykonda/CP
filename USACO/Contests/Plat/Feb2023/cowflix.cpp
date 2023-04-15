// n sqrt n sol that passes all test cases other than 20, 21, 23
// basic observation is that when we increment k either the number of components decreases or the previous k sol is incremented by the number of compononets
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name.length()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
vi range(int e) { return range(0, e); }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

int N;
vector<bool> active;
vector<vector<int>> adj;
vi o, p;
void dfs(int s, int e) {
    p[s] = e;
    o.pb(s);
    for(const int& u : adj[s])
        if(u != e)
            dfs(u, s);
}
vector<vector<int>> readj;

// calcs tree dp mentioned in editorial + dp to calculate the minimum number of components
vector<array<int, 2>> dp;
vector<array<int, 2>> sz;
vector<int> sol, comps;
void calc_dp(int k) {
    for(int i = 0; i < N; i++) { 
        dp[i][0] = 0;
        dp[i][1] = k + 1;
        sz[i][0] = 0;
        sz[i][1] = 1;
        for(int u : readj[i]) {
            if(dp[u][0] < dp[u][1] - k)
                dp[i][1] += dp[u][0], sz[i][1] += sz[u][0];
            else
                dp[i][1] += dp[u][1] - k, sz[i][1] += sz[u][1] - 1;
            if(dp[u][0] < dp[u][1])
                dp[i][0] += dp[u][0], sz[i][0] += sz[u][0];
            else 
                dp[i][0] += dp[u][1], sz[i][0] += sz[u][1];
        }
        if(active[i])
            dp[i][0] = N * N;
    }
    if(dp[N - 1][0] < dp[N - 1][1])
        sol[k] = dp[N - 1][0], comps[k] = sz[N - 1][0];
    else
        sol[k] = dp[N - 1][1], comps[k] = sz[N - 1][1];
}


void divide_and_conquer(int l, int r) {
    if(r - l <= 1) return;
    if(comps[l] == comps[r]) {
        for(int i = l + 1; i < r; i++)
            sol[i] = sol[i - 1] + comps[l];
    } else {
        int m = (l + r) / 2;
        calc_dp(m);
        divide_and_conquer(l, m);
        divide_and_conquer(m, r);
    }
}

int main() {
    setio();
    cin >> N;
    string s; cin >> s;
    adj.resize(N);
    for(int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    // calculate parent of each node and the order for dp calculations
    p.resize(N);
    dfs(0, -1);
    reverse(o.begin(), o.end());
    vector<int> ro(N);
    for(int i = 0; i < N; i++) ro[o[i]] = i;
    readj.resize(N);
    for(int i = 0; i < N; i++)
        for(int u : adj[i])
            if(p[i] != u)
                readj[ro[i]].push_back(ro[u]);
    active.resize(N);
    for(int i = 0; i < N; i++) active[ro[i]] = s[i] == '1';

    // keeps track of our answers and # of components
    sol.resize(N + 1), comps.resize(N + 1), dp.resize(N), sz.resize(N);
    calc_dp(1), calc_dp(N);
    divide_and_conquer(1, N);
    for(int i = 1; i <= N; i++) cout << sol[i] << '\n';
}