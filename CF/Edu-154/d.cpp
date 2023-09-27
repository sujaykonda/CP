#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    vector<int> suff(n + 1); suff[n] = suff[n - 1] = 0;
    for(int i = n - 2; i >= 0; i--) suff[i] = suff[i + 1] + (a[i] >= a[i + 1]);
    int ans = suff[0];
    int pref = 0;
    for(int i = 0; i < n; i++) {
        if(i > 0) pref += a[i] >= a[i - 1];
        ans = min(pref + 1 + suff[i + 1], ans);
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}