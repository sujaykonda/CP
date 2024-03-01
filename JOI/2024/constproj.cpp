#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll N, M; cin >> N >> M;
    ll S, T, L, K; cin >> S >> T >> L >> K;
    S--, T--;
    vector<vector<pair<int, ll>>> adj(N);
    for(int i = 0; i < M; i++) { 
        ll A, B, C; cin >> A >> B >> C;
        A--, B--;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }
    auto djistra = [&] (int st) {
        vector<ll> d(N, -1);
        priority_queue<pair<ll, int>> pq;
        pq.push({0, st});
        while(pq.size() > 0) {
            int s = pq.top().second;
            ll nd = -pq.top().first;
            pq.pop();
            if(d[s] != -1) continue;
            d[s] = nd;
            for(auto [u, v] : adj[s]) {
                if(d[u] == -1) {
                    pq.push({-(v + nd), u});
                }
            }
        }
        return d;
    };
    vector<ll> d1 = djistra(S), d2 = djistra(T);
    if(d1[T] != -1 && d1[T] <= K) {
        cout << ((ll) N * (N - 1)) / 2 << endl;
    } else {
        ll ans = 0;
        sort(d2.begin(), d2.end());
        for(int i = 0; i < N; i++) {
            if(d1[i] != -1) {
                int j = max(0, (int)(upper_bound(d2.begin(), d2.end(), K - L - d1[i]) - upper_bound(d2.begin(), d2.end(), -1)));
                ans += j;
            }
        }
        cout << ans << endl;
    }
}   