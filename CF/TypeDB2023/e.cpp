#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k, x; rd(n, k, x);
    int xsum = 0;
    for(int i = 1; i <= n; i++) xsum ^= i;
    if(xsum != (k % 2) * x) {
        cout << "NO" << endl;
        return;
    }
    vector<pair<int, int>> v;
    vector<bool> done(n + 1);
    for(int i = 1; i <= n; i++) {
        if(v.size() == k - 1) break;
        if(!done[i] && 0 < (x ^ i) && (x ^ i) <= n && !done[x ^ i]) {
            v.push_back({i, x ^ i});
            done[i] = true;
            done[x ^ i] = true;
        }
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) cnt += !done[i];
    if(cnt == 0 || v.size() < k - 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(auto [a, b] : v) cout << 2 << " " << a << " " << b << endl;
        cout << cnt;
        for(int i = 1; i <= n; i++)
            if(!done[i])
                cout << " " << i;
        cout << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}