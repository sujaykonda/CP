#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    int cnt = 0;
    vector<vector<int>> adj(N);
    vector<string> s(N);
    for(int i = 0; i < N; i++) {
        cin >> s[i];
    }
    for(int i = 0; i < N - 1; i++) {
        for(int j = N - i - 2; j >= 0; j--) {
            int v = s[j][i] - '0';
            int sm = 0;
            for(int k : adj[j]) {
                sm ^= (s[k][j + i - k] - '0');
            }
            if(v != sm) {
                adj[j].push_back(j + i + 1);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}