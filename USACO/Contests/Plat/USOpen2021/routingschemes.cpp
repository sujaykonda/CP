#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
array<int, 102> fac;

void tc() {
    int N, K; cin >> N >> K;
    string s; cin >> s;
    vector<vector<bool>> adj(N, vector<bool>(N));
    for(int i = 0; i < N; i++) {
        string bs; cin >> bs;
        for(int j = 0; j < N; j++)
            adj[i][j] = bs[j] == '1';
    }
    vector<int> deg(N);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) deg[i] += adj[i][j];
        deg[i] += s[i] == 'R';
    }
    int ans = 1;
    for(int i = 0; i < N; i++) ans = ((long long)ans * fac[deg[i]]) % MOD;
    if(K == 0) {
        cout << ans << endl;
        return;
    }
    vector<pair<int, int>> be;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if(adj[i][j])
                be.push_back({i, j});
        }
    }
    auto calc_dp = [&] (vector<int> starts, vector<int> ends) {
        map<vector<int>, int> mp;
        mp[starts] = 1;
        for(int L = 0; L < N; L++) {
            map<vector<int>, int> next;
            int ecnt = 0;
            for(int i : ends) ecnt += i == L;
            for(auto &[u, v] : mp) {
                int cnt = 0;
                for(int i = 0; i < u.size(); i++) cnt += (u[i] != ends[i] && u[i] == L);
                vector<int> a = u;
                int b = ((long long)v * fac[deg[L] - cnt - ecnt]) % MOD;
                vector<int> cur;
                vector<bool> taken(N);
                function<void()> apply = [&] () {
                    if(cur.size() == a.size()) {
                        next[cur] = (next[cur] + b) % MOD;
                        return;
                    }
                    if(a[cur.size()] != ends[cur.size()] && a[cur.size()] == L) {
                        for(int j = L + 1; j <= ends[cur.size()]; j++) {
                            if(adj[a[cur.size()]][j] && !taken[j]) {
                                cur.push_back(j);
                                taken[j] = true;
                                apply();
                                taken[j] = false;
                                cur.pop_back();
                            }
                        }
                    } else {
                        cur.push_back(a[cur.size()]);
                        apply();
                        cur.pop_back();
                    }
                };
                apply();
            }
            mp = next;
        }
        return mp[ends];
    };
    if(K == 1) {
        ans = (ans + MOD - calc_dp({be[0].second}, {be[0].first})) % MOD;
        cout << ans << endl;
        return;
    }
    if(K == 2) {
        ans = (ans + MOD - calc_dp({be[0].second}, {be[0].first})) % MOD;
        ans = (ans + MOD - calc_dp({be[1].second}, {be[1].first})) % MOD;
        ans = (ans + calc_dp({be[0].second, be[1].second}, {be[0].first, be[1].first})) % MOD;
        ans = (ans + MOD - calc_dp({be[0].second, be[1].second}, {be[1].first, be[0].first})) % MOD;
        cout << ans << endl;
    }
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    fac[0] = 1;
    for(int i = 1; i <= 101; i++) fac[i] = ((long long)fac[i - 1] * i) % MOD;
    int T; cin >> T;
    while(T--) tc();
}