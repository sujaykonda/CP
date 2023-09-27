#include <bits/stdc++.h>
using namespace std;

struct cmp {
    bool operator() (const set<int>& s1, const set<int>& s2) const {
        return s1.size() < s2.size();
    }
};

vector<int> res, c;
vector<vector<int>> ch;
vector<int> sz;
set<set<int>, cmp> cur;
void dfs(int s) {
    res[s] = 1;
    set<set<int>, cmp
    > nw;
    set<int> add;
    sz[s] = 0;
    for(int u : ch[s]) {
        if(add.count(c[u])) {
            res[s] = 0;
        }
        sz[s]++;
        add.insert(c[u]);
    }
    nw.insert(add);
    for(int u : ch[s]) {
        dfs(u);
        if(sz[s] < sz[u]) swap(nw, cur);
        for(set<int> st : cur) {
            auto [u, v] = nw.insert(st);
            if(u != nw.begin()) {
                for(int i : *prev(u)) {
                    if(!st.count(i)) {
                        res[s] = 0;
                    }
                }
            }
            if(++u != nw.end()) {
                for(int i : st) {
                    if(!(*u).count(i)) {
                        res[s] = 0;
                    }
                }
            }
        }
        sz[s] += sz[u];
        res[s] &= res[u];
    }
    cout << s << ": " << res[s] << endl;
    for(set<int> st : nw) {
        for(int i : st) cout << i << " ";
        cout << endl;
    }
    swap(nw, cur);
}

vector<int> beechtree(int N, int M, vector<int> P, vector<int> C) {
    c = C;
    sz = vector<int>(N);
    res = vector<int>(N);
    ch = vector<vector<int>>(N);
    for(int i = 1; i < N; i++) ch[P[i]].push_back(i);
    dfs(0);
    return res;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T--) {
        int N, M; cin >> N >> M;
        vector<int> P(N), C(N);
        for(int i = 0; i < N; i++) cin >> P[i];
        for(int i = 0; i < N; i++) cin >> C[i];
        vector<int> ans = beechtree(N, M, P, C);
        for(int i = 0; i < N; i++) cout << res[i] << " ";
        cout << endl;
    }
}