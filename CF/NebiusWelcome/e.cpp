#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define in :
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

int main() {
    setio();
    int n, m;
    cin >> n >> m;
    vector<int> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[b] |= 1 << a;
        adj[a] |= 1 << b;
    }
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    vector<pair<int, int>> cycles;
    for(int i = 0; i < n; i++)
        dp[(1 << i)][i] = i;
    for(int mask = 1; mask < (1 << n); mask++) {
        int highestbit = 0;
        for(int i = 0; i < n; i++)
            if(getbit(mask, i))
                highestbit = i;
        for(int i = 0; i < n; i++) {
            if(dp[mask][i] != -1) {
                for(int j = 0; j < n; j++) {
                    if(j < highestbit && getbit(adj[i], j))
                        if(!getbit(mask, j) && dp[mask ^ (1 << j)][j] == -1)
                            dp[mask ^ (1 << j)][j] = i;
                }
            }
        }
    }
    for(int mask = 1; mask < (1 << n); mask++) {
        vi a(n, -1);
        int adjmask = 0;
        for(int i = 0; i < n; i++) {
            if(getbit(mask, i))
                adjmask |= adj[i];
        }
        if(adjmask == ((1 << n) - 1)) {
            int highestbit = 0;
            for(int i = 0; i < n; i++)
                if(getbit(mask, i))
                    highestbit = i;
            for(int i = 0; i < n; i++) {
                if(dp[mask][i] != -1 && getbit(adj[i], highestbit)) {
                    
                    for(int j = 0; j < n; j++)
                        if(!getbit(mask, j))
                            for(int k = 0; k < n; k++)
                                if(getbit(mask, k) && getbit(adj[j], k))
                                    a[j] = k + 1;

                    int msk = mask, j = i;
                    while(msk > 0) {
                        int nmsk = msk ^ (1 << j);
                        int nj = dp[msk][j];
                        if(nmsk > 0)
                            a[j] = nj + 1;
                        msk = nmsk;
                        j = nj;
                    }
                    a[j] = i + 1;
                    cout << "Yes" << endl;
                    cout << a << endl;
                    return 0;
                }
            }
        }
    }
    
    cout << "No" << endl;
}