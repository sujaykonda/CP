#include <cplib/general.h>
using namespace std;

void tc() {
    int n, x; rd(n, x);
    
    vector<pair<int, int>> a;
    for(int i = 0; i < n; i++) {
        int v; rd(v);
        a.push_back({v, i});
    }
    sort(a.begin(), a.end());
    vector<int> b(n); rd(b);
    sort(b.begin(), b.end());
    rotate(b.begin(), b.begin() + x, b.end());
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(a[i].first > b[i]) {
            cnt++;
        }
    }
    if(cnt != x) {
        cout << "NO" << endl;
        return;
    }

    vector<int> ans(n);
    for(int i = 0; i < n; i++) ans[a[i].second] = b[i];
    cout << "YES" << endl;
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}