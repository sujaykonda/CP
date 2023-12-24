#include <bits/stdc++.h>
using namespace std;


int N, K;

bool check(vector<vector<int>> strip) {
    int n = strip.size(), m = strip[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(strip[i][j] == 3) return false;
        }
    }
    vector<vector<int>> d(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(strip[i][j] == 2) q.push({i, j}), d[i][j] = 0;
        }
    }
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if(x + 1 < n) {
            if(d[x + 1][y] == -1) {
                d[x + 1][y] = 1 + d[x][y];
                q.push({x + 1, y});
            }
        }
        if(y + 1 < m) {
            if(d[x][y + 1] == -1) {
                d[x][y + 1] = 1 + d[x][y];
                q.push({x, y + 1});
            }
        }
        if(x - 1 >= 0) {
            if(d[x - 1][y] == -1) {
                d[x - 1][y] = 1 + d[x][y];
                q.push({x - 1, y});
            }
        }
        if(y - 1 >= 0) {
            if(d[x][y - 1] == -1) {
                d[x][y - 1] = 1 + d[x][y];
                q.push({x, y - 1});
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(d[i][j] < 0 || d[i][j] > K) return false;
        }
    }
    return true;
}

int main() {
    cin >> N >> K;
    vector<vector<int>> garden(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> garden[i][j];
        }
    }
    long long ans = 0;
    for(int i = 0; i < N - 1; i++) {
        for(int r = 0; r < N; r++) {
            long long c = 0;
            for(int l = 0; l <= r; l++) {
                vector<vector<int>> strip(2, vector<int>(r - l + 1));
                for(int j = l; j <= r; j++) {
                    strip[0][j - l] = garden[i][j];
                    strip[1][j - l] = garden[i + 1][j];
                }
                c += check(strip);
            }
            ans += c;
        }
    }
    cout << ans << endl;
}