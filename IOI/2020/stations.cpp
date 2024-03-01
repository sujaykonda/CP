#include <bits/stdc++.h>
using namespace std;

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }
    int t = 0;
    vector<int> label(n);
    function<void(int, int, int)> dfs = [&] (int s, int e, int p) {
        if(!p) label[s] = t++;
        for(int u : adj[s]) {
            if(u != e) {
                dfs(u, s, p ^ 1);
            }
        }
        if(p) label[s] = t++;
    };
    dfs(0, -1, 0);
    return label;
}

int find_next_station(int s, int t, vector<int> c) {
    bool mn = true;
    for(int u : c) {
        if(u < s) {
            mn = false;
        }
    }
    if(mn) {
        int p = c.back();
        if(s <= t && t <= p - 1) {
            int prev = s + 1;
            for(int i = 0; i < c.size() - 1; i++) {
                if(prev <= t && t <= c[i]) {
                    return c[i];
                }
                prev = c[i] + 1;
            }
            assert(true);
        } else {
            return p;
        }
    } else {
        int p = c[0];
        if(p + 1 <= t && t <= s) {
            int prev = s - 1;
            for(int i = c.size() - 1; i > 0; i--) {
                if(c[i] <= t && t <= prev) {
                    return c[i];
                }
                prev = c[i] + 1;
            }
            assert(true);
        } else {
            return p;
        }
    }
}