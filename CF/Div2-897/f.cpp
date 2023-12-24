#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/math/hash.h>
using namespace std;
typedef vector<pair<int, int>> edges;

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
    if(n == 2) {
        cout << 1 << " " << 2 << endl;
        return 0;
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
        subhsh[s] = {cnt, hsh};
    };
    dfs(0, -1);
    vector<set<Hash>> all(n + 1);
    for(pair<int, Hash> hsh : subhsh) {
        all[hsh.first].insert(hsh.second);
    }
    vector<map<Hash, edges>> cur(2);
    cur[1][1] = {};
    int s = 2;
    while(true) {
        vector<map<Hash, edges>> trees(s + 1);
        trees[1][1] = {};
        for(int i = 1; i < s; i++) {
            for(auto &[na, nb] : cur[i]) {
                for(int j = 1; j + i <= s; j++) {
                    for(auto &[a, b] : trees[j]) {
                        edges sm = b;
                        for(auto &[u, v] : nb) {
                            sm.pb({u + j, v + j});
                        }
                        sm.pb({0, j});
                        trees[i + j][a + na * bpow(mult, 2 * j - 1)] = sm;
                    }
                }
            }
        }
        cur.emplace_back(trees[s]);
        for(auto [u, v] : cur[s]) {
            if(!all[s].count(u)) {
                for(int i = 1; i <= n - s; i++) {
                    cout << i << " " << i + 1 << endl;
                }
                for(auto [a, b] : v) {
                    cout << a + n - s + 1 << " " << b + n - s + 1 << endl;
                }
                return 0;
            } 
        }
        s++;
    }

}