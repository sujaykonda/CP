#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
const int BLOCK_SIZE = 2000;
const int MAXA = 200001;

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    vector<pair<int, int>> q(n);
    for(int i = 0; i < n; i++) {
        int l = max(0, i - k / 2), r = min(n - k, i);
        q[i] = {l + k - (i - l) - 1, r + k - (i - r) - 1};
    }
    vector<vector<array<int, MAXA>>> cnts(2, vector<array<int, MAXA>>((n - 1) / BLOCK_SIZE + 1));
    for(int i = 0; i < n; i++)
        cnts[i % 2][i / BLOCK_SIZE][a[i]]++;
    
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        if(q[i].first > q[i].second) continue;
        int j = q[i].first;
        ll cnt = 0;
        while(j <= q[i].second) {
            if(j + BLOCK_SIZE <= q[i].second && (j % BLOCK_SIZE == 0 || j % BLOCK_SIZE == 1)) {
                cnt += cnts[j % 2][j / BLOCK_SIZE][a[i]];
                j += BLOCK_SIZE;    
            } else {
                cnt += a[i] == a[j];
                j += 2;
            }
        }
        sum += (q[i].second - q[i].first) / 2 + 1 - cnt;
    }
    cout << sum << endl;
}