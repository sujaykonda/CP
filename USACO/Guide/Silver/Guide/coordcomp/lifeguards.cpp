// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

long long N;
vector<pair<long long, long long>> e;
pair<long long, long long> lgs[100001];
long long P[200001];
int main() {
	freopen("lifeguards.in", "r", stdin);
	freopen("lifeguards.out", "w", stdout);
	cin >> N;
	e.resize(2 * N);
	for(int i = 0; i < N; i++) {
		cin >> e[2 * i].first >> e[2 * i + 1].first;
		e[2 * i].second = i + 1;
		e[2 * i + 1].second = - i - 1;
	}
	sort(e.begin(), e.end());
	for(int i = 0; i < e.size(); i++) {
		long long lg = abs(e[i].second);
		if(e[i].second > 0) 
			lgs[lg].first = i;
		if(e[i].second < 0)
			lgs[lg].second = i;
	}
	long long base = 0;
	long long lc = 0;
	for(int i = 0; i < e.size() - 1; i++) {
		lc += e[i].second/abs(e[i].second);
		base += (lc > 0) * (e[i + 1].first - e[i].first);
		P[i + 1] = P[i] + (lc == 1) * (e[i + 1].first - e[i].first);
	}
	long long m = base;
	for(int i = 1; i <= N; i++)
		m = min(m, P[lgs[i].second] - P[lgs[i].first]);
	cout << base - m << endl;
}
