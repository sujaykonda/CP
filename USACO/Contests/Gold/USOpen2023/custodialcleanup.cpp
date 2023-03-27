// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void testcase() {
	int N, M; cin >> N >> M;
	vector<vector<int>> adj(N);
	vector<int> C(N), S(N), F(N);
	for(int i = 0; i < N; i++)
		cin >> C[i], C[i]--;
	for(int i = 0; i < N; i++)
		cin >> S[i], S[i]--;
	for(int i = 0; i < N; i++)
		cin >> F[i], F[i]--;
	for(int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	// simulate if you can get the keys
	vector<bool> reachable(N);
	vector<bool> keys(N);
	vector<vector<int>> blocked(N);
	queue<int> q;
	reachable[0] = true;
	q.push(0);
	while(!q.empty()) {
		int s = q.front();
		q.pop();
		keys[S[s]] = true;
		for(int u : blocked[S[s]]) {
			reachable[u] = true;
			q.push(u);
		}
		blocked[S[s]].clear();
		for(int u : adj[s]) {
			if(!reachable[u]) {
				if(keys[C[u]]) {
					reachable[u] = true;
					q.push(u);
				} else {
					blocked[C[u]].push_back(u);
				}
			}
		}
	}
	// check if all the keys you can get is all that needs changing
	for(int i = 0; i < N; i++) {
		if(!reachable[i] && F[i] != S[i]) {
			cout << "NO" << endl;
			return;
		}
	}
	// simulate putting keys in reverse
	vector<bool> rreachable(N);
	vector<bool> rkeys(N);
	vector<vector<int>> rblocked(N);
	rreachable[0] = true;
	q.push(0);
	while(!q.empty()) {
		int s = q.front();
		q.pop();
		rkeys[F[s]] = true;
		for(int u : rblocked[F[s]]) {
			rreachable[u] = true;
			q.push(u);
		}
		rblocked[F[s]].clear();
		for(int u : adj[s]) {
			if(reachable[u] && !rreachable[u]) {
				if(rkeys[C[u]] || F[u] == C[u]) {
					rreachable[u] = true;
					q.push(u);
				} else {
					rblocked[C[u]].push_back(u);
				}
			}
		}
	}
	// check if you can put all the keys you got
	if(reachable == rreachable)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}

int main() {
	int T; cin >> T;
	for(int i = 0; i < T; i++) testcase();
}