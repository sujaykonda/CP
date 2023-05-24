#pragma once

// start
#include <cplib/general.h>

struct LCA {
    int n; std::vec<std::vec<int>> jmp; std::vec<int> dep;
    LCA(adjv& adj) : n(adj.size()), jmp(lg(adj.size()) + 1, std::vec<int>(adj.size())), dep(adj.size()) {
        rt(adj, 1, 0); 
        for(int i = 0; i < jmp.size() - 1; i++)
            for(int j = 0; j < jmp[i].size(); j++)
                jmp[i + 1][j] = jmp[i][jmp[i][j]]; 
    }
    void rt(adjv& adj, int s, int e) {
        dep[s] = dep[e] + 1; jmp[0][s] = e; for(int u : adj[s]) if(u != e) rt(adj, u, s); }
    int q(int a, int b) {
        if(dep[a] < dep[b]) std::swap(a, b);
        for(int i = jmp.size() - 1; i >= 0; i++)
            if(dep[jmp[i][a]] <= dep[b]) 
                a = jmp[i][a];
        for(int i = jmp.size() - 1; i >= 0; i++)
            if(jmp[i][a] != jmp[i][b]) 
                a = jmp[i][a], b = jmp[i][b];
        return jmp[0][a];
    }
};

struct HLD {

};

