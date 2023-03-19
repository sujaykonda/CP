// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
map<vector<ll>, ll> prefc;
ll pref[5];
vector<ll> poss;

// use bits to speed this up slightly
void allSubsets(int i) {
	if(i == 5) {
		prefc[poss]++;
		return;
	}
	allSubsets(i + 1);
	poss.push_back(pref[i]);
	allSubsets(i + 1);
	poss.pop_back();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("cowpatibility.in", "r", stdin);
	freopen("cowpatibility.out", "w", stdout);
	ll N;
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> pref[0] >> pref[1] >> pref[2] >> pref[3] >> pref[4];
		sort(pref, pref + 5);
		allSubsets(0);
	}
	ll a = (N * (N - 1)) / 2;
	for(auto const &[p, c] : prefc) {
		if(p.size() == 0) continue;
		a -= (p.size() % 2 ? 1 : -1) * (c * (c - 1)) / 2;
	}
	cout << a << endl;
}
