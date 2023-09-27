#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int N, K;
vector<vector<int>> d, d2;
vector<vector<int>> pref, suff;

void _add_edge(int a, int b, vector<vector<int>>& dp, bool rev) {
    auto qd = [&] (int a, int b, int k) {
        if(rev) swap(a, b);
        if(k == 0) {
            if(a == b) return 0;
            else return INF;
        } else if(k == 1) {
            return d[a][b];
        } else if(k == 2) {
            return d2[a][b];
        } else if(k == 3) {
            int mn = INF;
            for(int i = 0; i < N; i++) {
                mn = min(mn, d2[a][i] + d[i][b]);
            }
            return mn;
        }
        return INF;
    };
    int s = rev ? b : a;
    int e = rev ? a : b;
    for(int j = 1; j < dp[0].size(); j++) {
        for(int k = 0; k < j; k++) {
            if(dp[s][k] != INF) {
                for(int i = 0; i < N; i++) {
                    dp[i][j] = min(dp[i][j], dp[s][k] + d[a][b] + qd(e, i, j - k - 1));
                }
            }
        }
    }
}

void add_edge(int a, int b, int c) {
    d[a][b] = c;
    for(int i = 0; i < N; i++) {
        d2[i][b] = min(d2[i][b], d[i][a] + d[a][b]);
    }
    for(int i = 0; i < N; i++) {
        d2[a][i] = min(d2[a][i], d[a][b] + d[b][i]);
    }
    _add_edge(a, b, pref, false);
    _add_edge(a, b, suff, true);
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> K;
    vector<vector<int>> w(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> w[i][j];
        }
    }
    vector<pair<int, int>> o(N * N);
    for(int i = 0; i < N * N; i++) {
        int a, b; cin >> a >> b;
        o[i] = {a - 1, b - 1};
    }
    reverse(o.begin(), o.end());
    vector<int> ans(N * N);
    d.resize(N, vector<int>(N, INF));
    d2.resize(N, vector<int>(N, INF));
    pref.resize(N, vector<int>(K / 2 + 1, INF));
    suff.resize(N, vector<int>((K + 1) / 2 + 1, INF));
    pref[0][0] = suff[N - 1][0] = 0;
    for(int i = 0; i < N * N; i++) {
        int mn = INF;
        for(int j = 0; j < N; j++) mn = min(mn, pref[j][K / 2] + suff[j][(K + 1) / 2]);
        if(mn == INF) mn = -1;
        ans[i] = mn;
        auto [a, b] = o[i];
        int c = w[a][b];
        add_edge(a, b, c);
    }
    reverse(ans.begin(), ans.end());
    for(int ai : ans) cout << ai << '\n';
}