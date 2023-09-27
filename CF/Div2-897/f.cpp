#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/math/hash.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    Hash mult;
    mult.a = uniform_int_distribution(99, 239)(rng);
    mult.b = uniform_int_distribution(99, 239)(rng);
    mult.c = uniform_int_distribution(99, 239)(rng);
    int n; rd(n);
    adjlist adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<pair<int, Hash>> subhsh(n);
    function<void(int, int)> dfs = [&] (int s, int e) {
        vector<pair<int, Hash>> hshs;
        for(int u : adj[s])
            if(u != e)
                dfs(u, s), hshs.pb(subhsh[u]);
        sort(hshs.begin(), hshs.end());
        Hash hsh = 1;
        int cnt = 1;
        for(int i = 0; i < hshs.size(); i++) {
            hsh += hshs[i].second * bpow(mult, 2 * cnt - 1);
            cnt += hshs[i].first;
        }
        subhsh[s] = make_pair(cnt, hsh);
    };
    map<int, set<Hash>> all;
    for(pair<int, Hash> hsh : subhsh) all[hsh.first].insert(hsh.second);
    dfs(0, -1);
    map<int, set<Hash>> cur;
    cur[1].insert(1);
}