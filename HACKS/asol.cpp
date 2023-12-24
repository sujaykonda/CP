#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    vector<vector<int>> garden(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> garden[i][j];
        }
    }
    long long ans = 0;
    for(int i = 0; i < N - 1; i++) {
        int lastWellCol = -1, lastWellRow = 0;
        int lastWellAns = 0;
        for(int j = 0; j < N; j++) {
            // update lastWell
            if(garden[i][j] == 2 || garden[i + 1][j] == 2) {
                int row = (garden[i + 1][j] == 2);
                if(j - lastWellCol > 2 * K - (row == lastWellRow)) 
                    lastWellAns = 0;
                lastWellAns += min(K, j - lastWellCol);
                lastWellCol = j;
                lastWellRow = row;
            }

            // reset if bad
            if(garden[i][j] == 3 || garden[i + 1][j] == 3) {
                lastWellCol = j;
                lastWellAns = 0;
            }
            if(j - lastWellCol < K) {
                ans += lastWellAns;
            }
        }
    }
    cout << ans << endl;
}