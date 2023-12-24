#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n; cin >> n;
    int m; cin >> m;
    vector<pair<int, int>> x(n);
    for(int i = 0; i < n; i++) cin >> x[i].first, x[i].second = i;
    sort(x.begin(), x.end());
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        int diff = -1;
        int prev = 1e9 + 1;
        bool good = true;
        for(auto [u, v] : x) {
            if(l <= v && v <= r) {
                if(prev != 1e9 + 1) {
                    if(diff == -1) {
                        diff = u - prev;
                    } else {
                        if(u - prev != diff) {
                            good = false;
                            break;
                        }
                    }
                }
                prev = u;
            }
        }
        if(good) cout << "YES ";
        else cout << "NO ";
    }
    cout << endl;
}