#include <bits/stdc++.h>
using namespace std;

int T, N, K;
int mx(vector<int> x, vector<int> y) {
    vector<array<int, 2>> dp(x.size() + 1, {-1, -1});
    dp[0][0] = 0;
    int j = 0;
    for(int i = 0; i < x.size(); i++) {
        while(j < x.size() && x[i] - x[j] > K) j++;
        dp[i + 1] = dp[i];
        if(dp[j][0] != -1 && (i == 0 || i == x.size() - 1 || i % 2 == 0 || x[i + 1] - x[i - 1] <= K))
            dp[i + 1][1] = max(dp[i + 1][1], y[i] + dp[j][0]);
        if(dp[j][1] != -1 && (i == 0 || i == x.size() - 1 || i % 2 == 1 || x[i + 1] - x[i - 1] <= K))
            dp[i + 1][0] = max(dp[i + 1][0], y[i] + dp[j][1]);
    }
    return dp[x.size()][x.size() % 2];
}
int mn(vector<int> x, vector<int> y) {
    if(x.size() % 2 == 0) return 0;
    int mny = y[0];
    for(int i = 0; i < y.size(); i++)
        if(i % 2 == 0 || x[i + 1] - x[i - 1] <= K)
            mny = min(mny, y[i]);
    return mny;
}

int main() {
    cin >> T >> N >> K;
    vector<int> x, y;
    int v = 0;
    for(int i = 0; i < N; i++) {
        int xi, yi;
        cin >> xi >> yi;
        if(x.size() > 0 && x.back() + K < xi) {
            if(T == 1)
                v += mn(x, y);
            else
                v += mx(x, y);
            x.clear(), y.clear();
        }
        x.push_back(xi), y.push_back(yi);
    }
    if(T == 1)
        v += mn(x, y);
    else
        v += mx(x, y);
    cout << v << endl;
}