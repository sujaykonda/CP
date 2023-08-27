#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int k; for(k = 1; k <= n; k *= 2);
    ll ans = 0;
    for(int i = 0; i * i < k; i++) {
        vector<int> cnt(k);
        int cur = 0;
        for(int j = 0; j < n; j++) {
            cnt[cur]++;
            cur ^= a[j];
            ans += cnt[cur ^ (i * i)];
        }
    }
    cout << ((ll)n * (n + 1)) / 2 - ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}