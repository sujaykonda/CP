#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<vector<int>> a(n);
    for(int i = 0; i < n; i++) {
        int mi; rd(mi);
        a[i].resize(mi); rd(a[i]);
        sort(a[i].begin(), a[i].end());
    }

    ll ans = 0;
    int mn = a[0][1];
    int mn2 = a[0][0];
    for(int i = 0; i < n; i++) {
        ans += a[i][1];
        mn = min(a[i][1], mn);
        mn2 = min(a[i][0], mn2);
    }

    cout << ans - mn + mn2 << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}