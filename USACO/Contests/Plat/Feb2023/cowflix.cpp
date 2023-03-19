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

// calcs tree dp mentioned in editorial + dp to calculate the minimum number of components
vector<array<int, 2>> dp;
vector<array<int, 2>> sz;
void calc_dp(int k, int& cost, int& comps) {
    for(int i : o) {
        dp[i][0] = 0;
        dp[i][1] = k + 1;
        sz[i][0] = 0;
        sz[i][1] = 1;
        for(int u : adj[i]) {
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
    if(dp[0][0] < dp[0][1])
        cost = dp[0][0], comps = sz[0][0];
    else
        cost = dp[0][1], comps = sz[0][1];
}


int main() {
    setio();
    cin >> N;
    string s; cin >> s;
    active.resize(N);
    for(int i = 0; i < N; i++) active[i] = s[i] == '1';
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
    // remove all parents from adjacency (idk if this actually speeds stuff up)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < adj[i].size(); j++) {
            if(adj[i][j] == p[i]) {
                adj[i].erase(adj[i].begin() + j);
                break;
            }
        }
    }
    reverse(o.begin(), o.end());

    // keeps track of our answers and # of components
    vector<int> sol(N);
    vector<int> comps(N);
    dp.resize(N), sz.resize(N);
    for(int i = 0; i < N; i++) {
        // if we havent calculated the sol yet, calculate it
        if(comps[i] == 0) {
            calc_dp(i + 1, sol[i], comps[i]);
            // binary searches the furthest k with the same amount of components
            int l = i, r = N - 1;
            while (l < r) {
                int m = (l + r + 1) / 2;
                if(comps[m] == 0)
                    calc_dp(m + 1, sol[m], comps[m]);
                if(comps[m] >= comps[i])
                    l = m;
                else
                    r = m - 1;
            }
            // every time we increment k the answer increases by the number of componenets
            for(int j = i + 1; j <= l; j++) {
                sol[j] = sol[j - 1] + comps[i];
                comps[j] = sol[j];
            }
        }
    }
    for(int i = 0; i < N; i++) cout << sol[i] << '\n';
}