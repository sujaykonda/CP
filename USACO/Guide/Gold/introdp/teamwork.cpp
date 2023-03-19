// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int dp[10001];
int main() {
	freopen("teamwork.in", "r", stdin);
	freopen("teamwork.out", "w", stdout);
	int N, K;
	cin >> N >> K;
	vector<int> skills(N + 1);
	for(int i = 1; i <= N; i++) cin >> skills[i];
	for(int i = 1; i <= N; i++) {
		int mx = skills[i];
		for(int j = i; j > i - K && j > 0; j--) {
			mx = max(skills[j], mx);
			dp[i] = max(dp[i], dp[j - 1] + (i - j + 1) * mx);
		}
	}
	cout << dp[N] << endl;
}
