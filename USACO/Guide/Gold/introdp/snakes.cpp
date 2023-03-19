// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int dp[401][401];
int cost[401][401];

int main() {
	freopen("snakes.in", "r", stdin);
	freopen("snakes.out", "w", stdout);
	int N, K;
	cin >> N >> K;
	vector<int> groups(N);
	for(int i = 0; i < N; i++)
		cin >> groups[i];
	for(int i = 0; i < N; i++) {
		int mx = groups[i];
		cost[i][i] = 0;
		for(int j = i + 1; j < N; j++) {
			int nmx = max(mx, groups[j]);
			cost[i][j] = cost[i][j - 1] + (nmx - mx) * (j - i) + nmx - groups[j];
			mx = nmx;
		}
	}
	for(int i = 1; i < N; i++) {
		dp[i][0] = cost[0][i];
	}
	for(int k = 1; k <= K; k++) {
		for(int i = 1; i < N; i++) {
			dp[i][k] = cost[0][i];
			for(int j = i; j > 0; j--) {
				dp[i][k] = min(dp[i][k], dp[j - 1][k - 1] + cost[j][i]);
			}
		}
	}
	int best = INT_MAX;
	for(int k = 0; k <= K; k++) {
		best = min(best, dp[N - 1][k]);
	}
	cout << best << endl;
}
