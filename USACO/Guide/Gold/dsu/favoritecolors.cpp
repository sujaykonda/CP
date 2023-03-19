// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<set<int>> adj;
vector<set<int>> radj;

// parent array
vector<int> p;

void merge(int a, int b) {
    // ensures the least number of insertions into the set
	if(radj[a].size() < radj[b].size()) swap(a, b);
	p[b] = a;
    // merges adj while also replacing any instances of b with a
	for(int u : adj[b]) {
		radj[u].erase(b);
		radj[u].insert(a);
		adj[a].insert(u);
	}
    // merges radj while also replacing any instances of b with a
	for(int u : radj[b]) {
		adj[u].erase(b);
		adj[u].insert(a);
		radj[a].insert(u);
	}
}

int main() {
	freopen("fcolor.in", "r", stdin);
	freopen("fcolor.out", "w", stdout);

	cin >> N >> M;
	adj.resize(N);
	radj.resize(N);
	p.resize(N, -1);
	queue<int> merging;
	for(int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		radj[a].insert(b);
		adj[b].insert(a);
	}
    // find any things that need merging
	for(int i = 0; i < N; i++) 
		if(radj[i].size() > 1)
			merging.push(i);
    // merge things until no more merging is necessary
	while(!merging.empty()) {
		int s = merging.front();
        // get highest parent of s
		while(p[s] > -1) s = p[s];
		merging.pop();
        // merge until only one radj
		while(radj[s].size() > 1) merge(*radj[s].begin(), *(++radj[s].begin()));
		int c = *radj[s].begin();
        // check if that one radj needs merging
		if(radj[c].size() > 1) merging.push(c);
	}
    // assign color in the most lexographically smallest way
	vector<int> c(N);
	int co = 1;
	for(int i = 0; i < N; i++) {
		int s = i;
		while(p[s] > -1) s = p[s];
		if(c[s] == 0) c[s] = co++;
		c[i] = c[s];
	}
    // print color!!!
	for(int i = 0; i < N; i++)
		cout << c[i] << endl;
}
