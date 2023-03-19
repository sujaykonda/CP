// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define inf 250000000ll
using ll = long long;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, K;
	cin >> N >> K;
	vector<int> b(N);
	for(int i = 0; i < N; i++) cin >> b[i], b[i]--;
	vector<vector<int>> S(K, vector<int>(K));
	for(int i = 0; i < K; i++) {
		string ln;
		cin >> ln;
		for(int j = 0; j < K; j++)
			S[i][j] = ln[j] == '1';
	}
	vector<ll> dist(N, inf);
	dist[0] = 0;

	vector<vector<ll>> mins(N, vector<ll>(K, inf));
	mins[0][b[0]] = dist[0];
    // optimized bellman-ford algorithm
	for(int k = 0; k < K; k++) {
		for(int i = 1; i < N; i++) {
			mins[i] = mins[i - 1];
			mins[i][b[i]] = min(mins[i][b[i]], dist[i]);
		}
	    vector<int> front(K, N);
		for(int i = N - 1; i > 0; i--) {
			for(int j = 0; j < K; j++) {
				if(S[j][b[i]] && b[i] != j) {
					dist[i] = min(dist[i], mins[i][j]);
					if(front[j] < N)
						dist[i] = min(dist[i], dist[front[j]] + front[j] - i);
				}
			}
			if(front[b[i]] == N || dist[i] + i < dist[front[b[i]]] + front[b[i]])
				front[b[i]] = i;
		}
	}
	if(dist[N - 1] == inf)
		cout << -1 << '\n';
	else
		cout << N - 1 + 2 * dist[N - 1] << '\n';
}
