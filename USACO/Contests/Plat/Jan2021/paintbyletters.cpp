#include <bits/stdc++.h>
using namespace std;


vector<vector<pair<int, int>>> edges;

void add(int l, int r, pair<int, int> edge, int s, int lb, int rb) {
    l = max(l, lb), r = min(r, rb);
    if(r < l) return;
    if(l == lb && r == rb) {
        edges[s].push_back(edge);
        return;
    }
    int m = (lb + rb) / 2;
    add(l, r, edge, 2 * s, lb, m);
    add(l, r, edge, 2 * s + 1, m + 1, rb);
}

int main() {
    int N, M, Q; cin >> N >> M >> Q;
    edges.resize(4 * Q);
    vector<vector<char>> c(N, vector<char>(M));
    for(int i = 0; i < N; i++) {
        string s; cin >> s;
        for(int j = 0; j < M; j++)
            c[i][j] = s[j];
    }
    
}