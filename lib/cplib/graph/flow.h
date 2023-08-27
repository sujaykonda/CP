#pragma once

// start
#include <cplib/general.h>

void ffdfs(wadjlist& _adj, int source, int sink) {
    int n = _adj.size();
    int m = 0; for(int i = 0; i < n; i++) m += _adj[i].size();
    adjlist adj(_adj.size());
    int j = 0, lim = 0;
    std::vector<std::pair<int, int>> e(2 * m);
    for(int i = 0; i < n; i++) {
        for(auto [u, v] : _adj[i]) {
            lim = std::max(lim, v);
            adj[i].pb(j); e[j] = {u, v};
            adj[u].pb(j + m); e[j + m] = {i, 0};
            j++;
        }
    }
    for(lim = (lim + 1) / 2; lim > 0; lim = (lim == 1 ? 0 : (lim + 1) / 2)) {
        std::vector<bool> done(n);
        int mn; bool con;
        auto dfs = [&] (int s, auto&& d) {
            if(s == sink) {
                con = true;
                return;
            }
            done[s] = true;
            for(int i : adj[s]) {
                int prev = mn;
                int u = e[i].first, v = e[i].second;
                mn = std::min(mn, v);
                if(!done[u] && v >= lim) {
                    d(u, d);
                    if(con) {
                        e[i].second -= mn;
                        e[i - m + (i < m) * 2 * m].second += mn;
                        return;
                    }
                }
                mn = prev;
            }
        };
        do {
            std::fill(done.begin(), done.end(), false);
            mn = lim * 2; con = false;
            dfs(source, dfs);
        } while(con);
    }
    for(int i = 0; i < n; i++)
        for(auto& [u, v] : _adj[i])
            v = e[j++].second;
}