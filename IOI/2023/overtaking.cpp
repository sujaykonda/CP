#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 2e18;

ll g;
set<pair<ll, ll>> ans;
 
void init(int L, int N, vector<ll> T, vector<int> W, int X, int M, vector<int> S) {
    g = (ll) L * X;
    vector<pair<ll, int>> lines;
    for(int i = 0; i < N; i++) {
        if(W[i] > X) {
            lines.push_back({T[i], W[i] - X});
        }
    }
    sort(lines.begin(), lines.end());
    lines.resize(unique(lines.begin(), lines.end()) - lines.begin());
    vector<vector<ll>> t(lines.size(), vector<ll>(M));
    vector<vector<bool>> inter(lines.size(), vector<bool>(M));
    vector<int> o(lines.size());
    for(int i = 0; i < lines.size(); i++) t[i][0] = lines[i].first, o[i] = i;
    for(int i = 0; i < M - 1; i++) {
        for(int j = 0; j < lines.size(); j++) {
            t[j][i + 1] = (ll)(S[i + 1] - S[i]) * lines[j].second + t[j][i];
        }
        sort(o.begin(), o.end(), [&] (int a, int b) { return t[a][i] < t[b][i]; });
        ll mx = 0;
        int j = 0;
        for(int k : o) {
            while(t[o[j]][i] < t[k][i]) mx = max(mx, t[o[j++]][i + 1]);
            if(t[k][i + 1] <= mx) {
                inter[k][i + 1] = true;
                t[k][i + 1] = mx;
            }
        }
    }
    ans.insert({0, 0});
    for(int i = M - 2; i >= 0; i--) {
        sort(o.begin(), o.end(), [&] (int a, int b) { return t[a][i] < t[b][i]; });
        for(int j : o) {
            if(!inter[j][i + 1]) {
                pair<ll, ll> p = {t[j][i] + 1, t[j][i + 1]};
                auto o = prev(ans.lower_bound(make_pair(t[j][i + 1], INF)));
                if(p.second < (*o).second) {
                    if((*o).first < p.first) continue;
                    p.second = (*o).second;
                }
                while((*o).first > p.first) {
                    o = ans.erase(o);
                    o--;
                }
                ans.insert(p);
            }
        }
    }
}
 
ll arrival_time(ll Y) {
    return max(Y, (*prev(ans.lower_bound(make_pair(Y, INF)))).second) + g;
}


int main() {
    int L, N, X, M, Q; cin >> L >> N >> X >> M >> Q;
    vector<ll> T(N);
    for(int i = 0; i < N; i++) cin >> T[i];
    vector<int> W(N);
    for(int i = 0; i < N; i++) cin >> W[i];
    vector<int> S(M);
    for(int i = 0; i < M; i++) cin >> S[i];
    init(L, N, T, W, X, M, S);
    for(int i = 0; i < Q; i++) {
        ll Y; cin >> Y;
        cout << arrival_time(Y) << '\n';
    }
}