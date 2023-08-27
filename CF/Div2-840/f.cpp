#include <bits/stdc++.h>
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n' 
typedef std::vector<std::vector<int>> adjlist;
typedef std::vector<std::vector<std::pair<int, int>>> wadjlist;

template<class T> T _max(T a, T b) { return (a > b) ? a : b; }
template<class T> T _min(T a, T b) { return (b > a) ? a : b; }
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
template<class T> T bpow(T a, long long p) { assert(p >= 0); return p == 0 ? T(1) : bpow(a * a, p / 2) * (p & 1 ? a : T(1)); }
void rd(char& x) { x = std::getchar(); }
void rd(ll& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(int& x) { ll y; rd(y); x = y; }
void rd(std::string& s) {
    s = ""; char c; rd(c);
    for(; !isgraph(c); rd(c));
    for(; isgraph(c); rd(c))
        s += c;
}
void rdg(adjlist& adj, int m, bool b1 = true, bool b2 = false) {
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
template<class T, typename ... R> void rd(T& a, R&... r) {
    rd(a), rd(r...); }

std::string str(char c) { return std::string(1, c); } std::string str(std::_Bit_reference b) { return b ? "T" : "F"; }
std::string str(int x) { return std::to_string(x); } std::string str(ll x) { return std::to_string(x); }
template<class T> std::string str(T a); template<class T, int S> std::string str(std::array<T, S>&);
template<class T, class U> std::string str(std::pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> std::string str(std::array<T, S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> std::string str(T a) { std::string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> std::string strnl(T a) { std::string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
struct LCA {
    int n; std::vector<std::vector<int>> jmp; std::vector<int> dep;
    LCA(adjlist& adj) : n(adj.size()), jmp(lg(n) + 1, std::vector<int>(n)), dep(n) {
        rt(adj, 1, 0); 
        for(int i = 0; i < jmp.size() - 1; i++)
            for(int j = 0; j < n; j++)
                jmp[i + 1][j] = jmp[i][jmp[i][j]]; 
    }
    void rt(adjlist& adj, int s, int e) {
        dep[s] = dep[e] + 1; jmp[0][s] = e; for(int u : adj[s]) if(u != e) rt(adj, u, s); }
    int q(int a, int b, std::pair<int, int>& ab) {
        if(dep[a] < dep[b]) std::swap(a, b);
        for(int i = jmp.size() - 1; i >= 0; i--)
            if(dep[jmp[i][a]] >= dep[b]) 
                a = jmp[i][a];
        if(a == b) return a;
        for(int i = jmp.size() - 1; i >= 0; i--)
            if(jmp[i][a] != jmp[i][b]) 
                a = jmp[i][a], b = jmp[i][b];
        ab.first = a, ab.second = b;
        return jmp[0][a];
    }
};

using namespace std;

int main() {
    int n, m; rd(n, m);
    adjlist adj(n + 1);
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b); 
        adj[a].pb(b); adj[b].pb(a);
    }
    vector<int> d(n + 1, -1), h(n + 1), v(n + 1);
    for(int i = 1; i <= n; i++) h[i] = i;

    adjlist tadj(n + 1);
    auto dfs = [&] (int s, auto&& dfs) {
        if(s == 0) return;
        for(int u : adj[s]) {
            if(d[u] == -1) {
                d[u] = d[s] + 1;
                dfs(u, dfs);
                if(h[u] == u) {
                    tadj[s].pb(u);
                    tadj[u].pb(s);
                } else {
                    h[s] = h[u];
                }
            }
            else if(d[u] < d[h[s]] - 1) {
                h[s] = u;
            }
        }
        if(h[s] != s) {
            for(int u : adj[s]) {
                if(d[u] < d[s]) {
                    v[h[s]]++;
                }
            }
            tadj[s].pb(h[s]);
            tadj[h[s]].pb(s);
        }
    };
    d[1] = 0;
    dfs(1, dfs);
    LCA lca(tadj);
    vector<int> nv(n + 1);
    for(int i = 1; i <= n; i++) {
        if(h[i] != lca.jmp[0][i]) {
            nv[i] = -v[lca.jmp[0][i]];
        }
    }
    vector<vector<int>> so(n + 1);
    for(int i = 1; i <= n; i++) so[lca.dep[i]].pb(i);
    vector<int> sm(n + 1);
    for(int i = 1; i <= n; i++) 
        for(int j : so[i])
            sm[j] = v[j] + nv[j] + sm[lca.jmp[0][j]];
    
    int q; rd(q);
    for(; q > 0; q--) {
        int a, b; rd(a, b);
        if(lca.dep[a] < lca.dep[b]) swap(a, b);
        pair<int, int> bc;
        int c = lca.q(a, b, bc);
        if(b == c) {
            cout << sm[a] - sm[b] + v[b] - v[a] << endl;
        } else {
            int ans = sm[a] + sm[b] - 2 * sm[c] + v[c] - v[a] - v[b];
            if(h[bc.first] == h[bc.second]) cout << ans << endl;
            else cout << ans + v[c] << endl;
        }
    }
}