#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/math/hash.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void tc() {
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
    vector<pair<Hash, int>> subhsh(n);
    function<void(int, int)> dfs = [&] (int s, int e) {
        vector<pair<Hash, int>> hshs;
        for(int u : adj[s]) {
            if(u != e) {
                dfs(u, s);
                hshs.pb(subhsh[u]);
            }
        }
        sort(hshs.begin(), hshs.end());
        Hash hsh = 1;
        int cnt = 1;
        for(int i = 0; i < hshs.size(); i++) {
            hsh += hshs[i].first * bpow(mult, 2 * cnt - 1);
            cnt += hshs[i].second;
        }
        subhsh[s] = make_pair(hsh, cnt);
    };
    dfs(0, -1);
    bool good = true;
    function<void(int, int)> dfs2 = [&] (int s, int e) {
        map<pair<Hash, int>, vector<int>> mp;
        for(int u : adj[s]) {
            if(u != e) {
                mp[subhsh[u]].pb(u);
            }
        }
        vector<int> odd;
        for(auto& [u, v] : mp) {
            if(v.size() % 2 == 1) odd.pb(v.back());
        }
        if(odd.size() > 1) good = false;
        else if(odd.size() == 1) dfs2(odd[0], s);
    };
    dfs2(0, -1);
    if(good) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}