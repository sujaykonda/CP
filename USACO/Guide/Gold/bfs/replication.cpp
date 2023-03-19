// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, D;
vector<vector<bool>> start;
vector<vector<int>> centers;
vector<vector<bool>> grid;
vector<vector<int>> dist;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool inbound(int x, int y) {
	return x < N && x >= 0 && y < N && y >= 0;
}

void calc_dist() {
	queue<pair<int, int>> q;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(!grid[i][j])
				q.push({i, j}), dist[i][j] = 0;
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++) {
			if(inbound(x + dx[i], y + dy[i]) && dist[x + dx[i]][y + dy[i]] == -1) {
				dist[x + dx[i]][y + dy[i]] = dist[x][y] + 1;
				q.push({x + dx[i], y + dy[i]});
			}
		}
	}
}

void calc_centers() {
    queue<pair<pair<int, int>, int>> q;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(start[i][j])
                q.push({{i, j}, 0});
    while(!q.empty()) {
        int x = q.front().first.first, y = q.front().first.second, m = q.front().second;
        q.pop();
        if(centers[x][y] != 0) continue;
        if(dist[x][y] < m / D + 1) {
            if(m % D == 0 && dist[x][y] >= m / D)
                centers[x][y] = dist[x][y];
            continue;
        }
        centers[x][y] = dist[x][y];
        for(int i = 0; i < 4; i++)
            q.push({{x + dx[i], y + dy[i]}, m + 1});
    }
}

int main() {
	cin >> N >> D;
    start.resize(N, vector<bool>(N));
	grid.resize(N, vector<bool>(N));
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			char c;
			cin >> c;
			grid[i][j] = (c != '#');
			if(c == 'S')
				start[i][j] = true;
		}
	}
	dist.resize(N, vector<int>(N, -1));
    calc_dist();

    centers.resize(N, vector<int>(N));
    calc_centers();


    priority_queue<pair<int, pair<int, int>>> pq;
    vector<vector<bool>> done(N, vector<bool>(N));
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(centers[i][j] > 0)
                pq.push({centers[i][j], {i, j}});
    
    while(!pq.empty()) {
        int c = pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
        pq.pop();
        if(done[x][y]) continue;
        done[x][y] = true;
        if(c == 1) continue;
        for(int d = 0; d < 4; d++)
            if(inbound(x + dx[d], y + dy[d])) 
				pq.push({c - 1, {x + dx[d], y + dy[d]}});
    }
    int cnt = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cnt += done[i][j];
    cout << cnt << endl;
}
