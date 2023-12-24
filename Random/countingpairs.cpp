#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 1;

int main() {
    vector<long long> ans(MX);
    for (int i = 0; i < MX; i++) ans[i] = i;

    for (int i = 2; i < MX; i++) {
        if (ans[i] == i) {
            for (int j = i; j < MX; j += i)
                ans[j] -= ans[j] / i;
        }
    }

    for(int i = 2; i < MX; i++) ans[i] += ans[i - 1];


    int t; cin >> t;
    while(t--) {
        int k; cin >> k;
        cout << ans[k] << endl;
    }
}
