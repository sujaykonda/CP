#include <bits/stdc++.h>
using ll = long long;
#define vec vector
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
typedef std::vec<std::vec<int>> adjv;

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
void rd(char& x) { x = std::getchar(); }
void rd(ll& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(int& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(std::string& s) {
    s = ""; char c; rd(c);
    for(; !isgraph(c); rd(c));
    for(; isgraph(c); rd(c))
        s += c;
}
void rd(adjv& adj, int m, bool b1 = true, bool b2 = false) {
    for(int i = 0; i < m; i++) {
        int a, b; rd(a), rd(b);
        if(b1) adj[a].pb(b);
        if(b2) adj[b].pb(a);
    }
}
template<class T> void rd(T&); template<class T, int S> void rd(std::array<T, S>&); 
template<class T, class U> void rd(std::pair<T, U>& p) { rd(p.first), rd(p.second); }
template<class T, int S> void rd(std::array<T, S>& a) { for(int i = 0; i < S; i++) rd(a[i]); }
template<class T> void rd(T& o)  { for(auto& v : o) rd(v); };

using namespace std;

vector<vector<int>> adj;
int main() {
    int n; rd(n);
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i ++) {
        int a, b; rd(a), rd(b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    
    vector<vector<int>> rts(n + 1);
    for(int rt = 1; rt <= n; rt++) {
        vector<int> d(n + 1, -1);
        queue<int> q;
        d[rt] = 0; q.push(rt);
        while(!q.empty()) {
            int s = q.front();
            rts[rt].pb(d[s]);
            q.pop();
            for(int u : adj[s]) {
                if(d[u] == -1) {
                    d[u] = d[s] + 1;
                    q.push(u);
                }
            }
        }
    }

    vector<ll> ans(n + 1, 0);
    for(int rt = 1; rt <= n; rt++) {
        ll sm = 0;
        for(int i = 0; i < n; i++) {
            sm += rts[rt][i];
            ans[i + 1] = max(ans[i + 1], (ll) (i + 1) * (n - 1) - 2 * sm);
        }
    }
    for(ll a : ans) cout << a << " ";
    cout << endl;
}  