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

vector<bool> done;
vector<bool> iadj;
vector<vector<int>> adj;

bool dfs(int s, vector<int>& p) {
    done[s] = true;
    for(int u : adj[s]) {
        if(!done[u]) {
            p.pb(u);
            if(iadj[u]) {
                return true;
            }
            if(dfs(u, p)) return true;
            p.pop_back();
        }
    }
    return false;
}

void testcase() {
    int n, m; cin >> n >> m;
    adj = vector<vector<int>>(n);
    done = vector<bool>(n);
    iadj = vector<bool>(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    for(int i = 0; i < n; i++) {
        if(adj[i].size() >= 4) {
            for(int u : adj[i])
                iadj[u] = true;
            for(int u : adj[i]) {
                fill(done.begin(), done.end(), false);
                done[i] = true;
                vector<int> p;
                p.pb(u);
                if(dfs(u, p)) {
                    cout << "YES" << endl;
                    cout << p.size() + 3 << endl;
                    int last = i;
                    for(int s : p) {
                        cout << last + 1 << " " << s + 1 << endl;
                        last = s;
                    }
                    cout << last + 1 << " " << i + 1 << endl;
                    int cnt = 0;
                    for(int u : adj[i]) {
                        if(u != p[0] && u != p.back()) {
                            cout << i + 1 << " " << u + 1 << endl; 
                            cnt++;
                            if(cnt == 2) break;
                        }
                    }
                    return;
                }
            }
            for(int u : adj[i])
                iadj[u] = false;
        }
    }
    cout << "NO" << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}