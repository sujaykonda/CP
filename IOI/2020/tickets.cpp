#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll find_maximum(int k, vector<vector<int>> x) {
    int n = x.size(), m = x[0].size();
    vector<vector<ll>> delta(n, vector<ll>(k));
    ll sm = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            sm -= x[i][j];
        }
        for(int j = 0; j < k; j++) {
            delta[i][j] = x[i][m - j - 1] + x[i][k - j - 1];
        }
    }
    vector<int> pos(n), neg(n, k);
    priority_queue<pair<ll, int>> pq;
    for(int i = 0; i < n; i++) {
        pq.push({delta[i][pos[i]], i});
    }
    for(int i = 0; i < n / 2 * k; i++) {
        sm += pq.top().first;
        int j = pq.top().second;
        pq.pop();
        pos[j]++;
        neg[j]--;
        if(pos[j] < k) pq.push({delta[j][pos[j]], j});
    }
    vector<vector<int>> s(n, vector<int>(m, -1));
    for(int i = 0; i < k; i++) {
        int negcnt = 0;
        vector<bool> used(n);
        for(int j = 0; j < n; j++) {
            if(pos[j] == 0) {
                used[j] = true;
                neg[j]--;
                s[j][neg[j]] = i;
                negcnt++;
            }
        }
        for(int j = 0; j < n; j++) {
            if(used[j]) continue;
            if(negcnt < n / 2 && neg[j] > 0) {
                neg[j]--;
                s[j][neg[j]] = i;
                negcnt++;
            } else {
                s[j][m - pos[j]] = i;
                pos[j]--;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << s[i][j] << " ";
        cout << endl;
    }
    return sm;
}

int main() {
    cout << find_maximum(1, {{0, 0, 1, 0},{1, 1, 0, 0}, {0, 1, 1, 1}, {0,1,1,0}}) << endl;
}