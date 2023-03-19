// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 1000000007

int N;

vector<pair<int, int>> intervals;
int main() {
	freopen("help.in", "r", stdin);
	freopen("help.out", "w", stdout);
	cin >> N;
	intervals.resize(N);
	for(int i = 0; i < N; i++) cin >> intervals[i].first >> intervals[i].second;
	
	sort(intervals.begin(), intervals.end());
	priority_queue<int, vector<int>, greater<int>> ep;
	ll a = 0;
	ll p2 = 1;
	for(int i = 0; i < N; i++) {
		while(ep.size() > 0 && intervals[i].first > ep.top())
			p2 = (2 * p2) % modn, ep.pop();
		a = (a * 2 + p2) % modn;
		ep.push(intervals[i].second);
	}
	cout << a << endl;
}
