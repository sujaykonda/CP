// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

string s;
int n;

int solvehalves(string left, string right, int sz) {
	int sum = 0;
	int lcnt = 0;
	int rcnt = 0;
	for(int i = 0; i < left.size(); i++)
		lcnt += left[i] == 'G', rcnt += right[i] == 'G';
	if(lcnt < rcnt) swap(left, right), swap(lcnt, rcnt);
	int i = 0, j = 0;
	while(lcnt > rcnt) {
		while(left[i] == 'H') i++;
		while(right[j] == 'G') j++;
		sum += sz + i + j + 1;
		swap(left[i], right[j]);
		lcnt--, rcnt++;
	}
	j = 0;
	for(int i = 0; i < left.size(); i++) {
		while(right[j] == 'H') j++;
		if(left[i] == 'G') {
			sum += abs(j - i);
			j++;
		}
	}
	return sum;
}

int singlecenter(bool good, int last, int c) {
	bool originallygood = good;
	int sum = 0;
	string left = "", right = "";
	for(int r = 1; c - r >= 0 && c + r < n; r++) {
		if(s[c - r] != s[c + r]) good = !good;
		left += s[c - r], right += s[c + r];
		if(good) {
			if(!originallygood) {
				last = -1;
				int i = 0;
				while(left[i] == s[c] && i < left.size()) i++;
				if(i < left.size()) {
					swap(s[c], left[i]);
					int mn = solvehalves(left, right, 1) + i + 1;
					swap(s[c], left[i]);
					if(last == -1 || last > mn) last = mn;
				}
				int j = 0;
				while(right[j] == s[c] && j < right.size()) j++;
				if(j < right.size()) {
					swap(s[c], right[j]);
					int mn = solvehalves(left, right, 1) + j + 1;
					swap(s[c], right[j]);
					if(last == -1 || last > mn) last = mn;
				}
				sum += last;
			} else {
				last = solvehalves(left, right, 1 + (r - left.size()) * 2);
				sum += last;
			}
			
		}
	}
	return sum;
}

int main() {
	cin >> s;
	n = s.length();
	int sum = 0;
	// double centers
	for(int i = 0; i < n - 1; i++) {
		int last = 0;
		bool good = true;
		string left = "", right = "";
		for(int r = 1; i - r + 1 >= 0 && i + r < n; r++) {
			if(s[i - r + 1] != s[i + r]) good = !good;
			left += s[i - r + 1], right += s[i + r];
			if(good) {
				last += solvehalves(left, right, (r - left.size()) * 2);
				left.clear(), right.clear();
				sum += last;
			} else {
				sum--;
			}
		}
	}
	// single centers (H)
	for(int i = 0; i < n; i++) {
		bool good = s[i] == 'H';
		int last = good ? 0 : -1;
		sum += singlecenter(good, last, i);
	}
	// single centers (G)
	for(int i = 0; i < n; i++) {
		bool good = s[i] == 'G';
		int last = good ? 0 : -1;
		sum += singlecenter(good, last, i);
	}
	cout << sum << endl;
}
