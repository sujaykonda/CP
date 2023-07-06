#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    vector<int> dp(n + 1, n);
    int cur = 0;
    for(int i = 0; i < n; i++) {
        int nxt = min(cur + 1, dp[a[i]]);
        dp[a[i]] = min(dp[a[i]], cur);
        cur = nxt;
    }
    cout << n - cur << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}