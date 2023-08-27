#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

void upd(ll& x, ll y) { x = max(x, y); }

int main() {
    int T, N, K; cin >> T >> N >> K;
    vector<ll> x(N), y(N);
    vector<int> h, g;
    for(int i = 0; i < N; i++) {
        char b; cin >> b;
        cin >> x[i] >> y[i]; 
        (b == 'H' ? h : g).push_back(i);
    }
    int H = h.size(), G = g.size();
    vector<vector<bool>> p(H, vector<bool>(G));
    for(int i = 0; i < H; i++)
        for(int j = 0; j < G; j++)
            p[i][j] = abs(x[h[i]] - x[g[j]]) <= K;
    
    ll ex = 0;
    vector<int> nh, ng;
    for(int i = 0; i < H; i++) {
        bool bad = true;
        for(int j = 0; j < G; j++)
            bad = bad && !p[i][j];
        if(!bad)
            nh.push_back(h[i]);
        else
            ex += y[h[i]];
    }
    for(int i = 0; i < G; i++) {
        bool bad = true;
        for(int j = 0; j < H; j++)
            bad = bad && !p[j][i];
        if(!bad)
            ng.push_back(g[i]);
        else
            ex += y[g[i]];
    }
    h = nh, g = ng;
    H = h.size(), G = g.size();
    p = vector<vector<bool>>(H, vector<bool>(G));
    for(int i = 0; i < H; i++)
        for(int j = 0; j < G; j++)
            p[i][j] = abs(x[h[i]] - x[g[j]]) <= K;

    if(T == 1) {
        vector<vector<ll>> dp(H + 1, vector<ll>(G + 1));
        for(int i = 0; i <= H; i++) {
            for(int j = 0; j <= G; j++) {
                if(i < H && j < G && p[i][j])
                    upd(dp[i + 1][j + 1], dp[i][j] + y[h[i]] + y[g[j]]);
                if(i < H)
                    upd(dp[i + 1][j], dp[i][j]);
                if(j < G)
                    upd(dp[i][j + 1], dp[i][j]);
            }
        }
        ll sm = 0;
        for(int i = 0; i < N; i++) sm += y[i];
        cout << sm - dp[H][G] << endl;
    } else {
        vector<vector<array<int, 2>>> t(H, vector<array<int, 2>>(G, {{-1, -1}}));
        for(int i = 0; i < H; i++) {
            int nextI = 0;
            for(int j = 1; j < G; j++) {
                while(nextI < H && x[h[nextI]] <= x[g[j - 1]] + K) nextI++;
                t[i][j][0] = max(i, nextI) - i;
            }
        }
        for(int j = 0; j < G; j++) {
            int nextJ = 0;
            for(int i = 1; i < H; i++) {
                while(nextJ < G && x[g[nextJ]] <= x[h[i - 1]] + K) nextJ++;
                t[i][j][1] = max(j, nextJ) - j;
            }
        }
        vector<vector<int>> mx(H + 1, vector<int>(G + 1));
        for(int i = H - 1; i >= 0; i--)
            for(int j = G - 1; j >= 0; j--)
                if(p[i][j]) mx[i][j] = 1 + mx[i + 1][j + 1];
        for(int i = 0; i < H; i++)
            for(int j = 0; j < G; j++)
                for(int k : {0, 1})
                    t[i][j][k] = (t[i][j][k] > mx[i][j]) ? -1 : t[i][j][k];

        vector<vector<array<ll, 2>>> dp(H + 1, vector<array<ll, 2>>(G + 1, {-INF, -INF})); 
        dp[0][0] = {0, 0};
        for(int i = 0; i <= H; i++) {
            for(int j = 0; j <= G; j++) {
                if(i < H && j < G) {
                    if(t[i][j][0] != -1) upd(dp[i + t[i][j][0]][j + t[i][j][0]][1], dp[i][j][0]);
                    if(t[i][j][1] != -1) upd(dp[i + t[i][j][1]][j + t[i][j][1]][0], dp[i][j][1]);
                }
                if(i < H) {
                    upd(dp[i + 1][j][1], dp[i][j][1] + y[h[i]]);
                }
                if(j < G) {
                    upd(dp[i][j + 1][0], dp[i][j][0] + y[g[j]]);
                }
                if(i < H && j < G && p[i][j]) {
                    upd(dp[i + 1][j + 1][0], dp[i][j][0]);
                    upd(dp[i + 1][j + 1][1], dp[i][j][1]);
                }
            }
        }
        cout << max(dp[H][G][0], dp[H][G][1]) + ex << endl;
    }
}