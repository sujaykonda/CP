#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MXD = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K; cin >> N >> K;
    vector<vector<int>> t(2 * N);
    auto add_range = [&] (int k, int l, int r) {
        for (l += N, r += N + 1; l < r; l /= 2, r /= 2) {
            if (l&1) t[l++].push_back(k);
            if (r&1) t[--r].push_back(k);
        }
    };
    
    vector<pair<int, int>> ti(K);
    vector<pair<int, int>> rnge(K);
    for(int i = 0; i < K; i++) {
        int c, p, a, b; 
        cin >> c >> p >> a >> b;
        a--, b--, c--;
        ti[i] = {c, p};
        rnge[i] = {a, b};
    }
    auto sp = [&] (vector<ll>& d) {
        for(int i = 0; i < 2 * N; i++) t[i].clear();
        for(int i = 0; i < K; i++)
            add_range(i, rnge[i].first, rnge[i].second);
        vector<bool> rem(K);
        priority_queue<pair<ll, int>> pq;
        for(int i = 0; i < N + K; i++)
            if(d[i] < MXD)
                pq.push({-d[i], i});
        for(int i = 0; i < N + K; i++) d[i] = MXD;
        while(!pq.empty()) {
            int s = pq.top().second;
            ll v = pq.top().first;
            pq.pop();
            if(d[s] <= -v) continue;
            d[s] = -v;
            if(s < N) {
                int n = s;
                s += N;
                while(s > 0) {
                    for(int i : t[s])
                        if(!rem[i])
                            pq.push({v, i + N}), rem[i] = true;
                    t[s].clear();
                    s /= 2;
                }
            } else {
                s -= N;
                pq.push({v - ti[s].second, ti[s].first});
            }
        }
    };
    
    vector<ll> d1(N + K, MXD), d2(N + K, MXD);
    d1[0] = d2[N - 1] = 0;
    sp(d1), sp(d2);
    vector<ll> d(N + K, MXD);
    for(int i = 0; i < N + K; i++)
        d[i] = min(d[i], d1[i] + d2[i]);
    sp(d);
    for(int i = 0; i < N; i++) {
        if(d[i] == MXD) cout << -1 << '\n';
        else cout << d[i] << '\n';
    }
}