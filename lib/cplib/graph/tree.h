#pragma once

// start
#include <cplib/general.h>

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
    int q(int a, int b) {
        if(dep[a] < dep[b]) std::swap(a, b);
        for(int i = jmp.size() - 1; i >= 0; i--)
            if(dep[jmp[i][a]] >= dep[b]) 
                a = jmp[i][a];
        if(a == b) return a;
        for(int i = jmp.size() - 1; i >= 0; i--)
            if(jmp[i][a] != jmp[i][b]) 
                a = jmp[i][a], b = jmp[i][b];
        return jmp[0][a];
    }
};