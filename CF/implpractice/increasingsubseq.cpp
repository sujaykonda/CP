#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define getbit(mask, i) ((mask & (1LL << i)) > 0)

void tc() {
    ll X; cin >> X;
    vector<int> ans;
    ll y = 1;
    int v = 0;
    while(2 * y <= X) {
        y *= 2;
        ans.push_back(v);
        v++;
    }
    X -= y;
    for(int i = 63; i >= 0; i--) {
        if(getbit(X, i)) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for(int i : ans) cout << i << " ";
    cout << endl;
}

int main() {
    int t; cin >> t;
    while(t--) tc();
}