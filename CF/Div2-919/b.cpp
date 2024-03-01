#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k, x; rd(n, k, x);
    vector<int> a(n); rd(a);
    sort(a.begin(), a.end());
    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) p[i + 1] = p[i] + a[i];
    int nonneg = n;
    for(int i = 0; i < n; i++) {
        if(a[i] > 0) {
            nonneg = i;
            break;
        }
    }
    ll best = -1e18;
    for(int i = 0; i <= k; i++) {
        best = max(best,  (-p[n - k + i] + 2 * p[max(nonneg, n - k + i - x)] + p[min(nonneg, i)]));
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}