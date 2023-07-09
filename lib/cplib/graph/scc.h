#pragma once

// start
#include <cplib/general.h>

struct _SCCData {
    std::vector<int> disc, low, instack;
    std::stack<int> st;
    int t, sccs;
};

void _sccdfs(int s, _SCCData& d, std::vector<int>& comp, adjlist& adj) {
    d.t = 0;
    d.disc[s] = d.low[s] = ++d.t;
    d.st.push(s); d.instack[s] = true;
    for(int u : adj[s]) {
        if(d.disc[u] == -1) {
            _sccdfs(u, d, comp, adj);
            d.low[s] = std::min(d.low[s], d.low[u]);
        }
        else if(d.instack[u])
            d.low[s] = std::min(d.low[s], d.disc[u]);
    }

}

int scc(int n, adjlist& adj) {

}