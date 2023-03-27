#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// debug tools
string str(_Bit_reference b) { return b ? "TRUE" : "FALSE"; }
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

void merge(int x, int y, vector<set<int>>& c) {
    for(int u : c[x])
        c[y].insert(u);
}

void dfs(int s, vector<set<int>>& c, vector<int>& merges_into, vector<int>& p) {
    for(int u : c[s]) dfs(u, c, merges_into, p);
    if(merges_into[s] == 0) {
        for(int u : c[s])
            if(merges_into[u] > 0)
                merges_into[s] = p[merges_into[u]];
    }
}

void dfs1(int s, vector<set<int>>& c, vector<int>& merges_into, vector<pair<int, int>>& merges) {
    //if(c[s].size() > 0)
        //assert(merges_into[*c[s].rbegin()] == -1);
    set<int> nc;
    for(int u : c[s]) {
        if(merges_into[u] == 0) {
            merges.push_back({u, *c[s].rbegin()});
            merge(u, *c[s].rbegin(), c);
        } else if(merges_into[u] > 0) {
            merges.push_back({u, merges_into[u]});
            merge(u, merges_into[u], c);
        } else nc.insert(u);
    }
    for(int u : nc) dfs1(u, c, merges_into, merges);
}
void testcase() {
    int N;
    cin >> N;
    vector<pair<int, int>> merges;
    vector<set<int>> c(N + 1);
    vector<int> p(N + 1);
    for(int i = 1; i < N; i++) {
        int vi, pi; cin >> vi >> pi;
        p[vi] = pi;
        c[pi].insert(vi);
    }
    vector<int> fp(N + 1);
    int M;
    cin >> M;
    for(int i = 1; i < M; i++) {
        int vi, pi; cin >> vi >> pi;
        fp[vi] = pi;
    }
    int root = 0;
    for(int i = 1; i <= N; i++)
        if(p[i] == 0)
            root = i;
    vector<int> merges_into(N + 1, -1);
    fp[root] = -1;
    for(int i = 1; i <= N; i++) {
        if(fp[i] == 0) merges_into[i] = 0;
        for(int u : c[i])
            if(fp[u] > 0 && fp[u] != i)
                merges_into[i] = fp[u];
    }
    //cout << str(merges_into) << endl;
    dfs(root, c, merges_into, fp);
    dfs1(root, c, merges_into, merges);
    cout << merges.size() << endl;
    for(pair<int, int> merge : merges)
        cout << merge.first << " " << merge.second << endl;
}

int main() {
    int T;
    cin >> T;
    for(int t = 0; t < T; t++) testcase();
}