#pragma once

// start
#include <cplib/general.h>

struct _SCCData {
    std::vector<int> disc, low;
    std::vector<bool> instack;
    std::stack<int> st;
    int t, sccs;
};

void _sccdfs(int s, _SCCData& d, std::vector<int>& comp, adjlist& adj) {
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
    int w = 0;
    if(d.low[s] == d.disc[s]) {
        while(d.st.top() != s) {
            w = d.st.top();
            comp[w] = d.sccs;
            d.instack[w] = false;
            d.st.pop();
        }
        w = d.st.top();
        comp[w] = d.sccs;
        d.instack[w] = false;
        d.st.pop();
        d.sccs++;
    }
}

int findSCC(std::vector<int>& comp, adjlist& adj) {
    int n = adj.size();
    _SCCData d;
    d.disc = d.low = std::vector<int>(n, -1);
    d.instack = std::vector<bool>(n);
    d.st = std::stack<int>();
    d.t = 0, d.sccs = 0;
    for(int i = 0; i < n; i++)
        if(d.disc[i] == -1)
            _sccdfs(i, d, comp, adj);
    return d.sccs;
}
