#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    vector<int> a(n); rd(a);
    sort(a.begin(), a.end());
    vector<vector<int>> fac(n);
    for(int i = 0; i < n; i++) {
        for(int j = 1; j * j <= a[i] && j <= m; j++) {
            if(a[i] % j == 0) {
                fac[i].pb(j);
                if(j * j != a[i] && a[i] / j <= m) 
                    fac[i].pb(a[i] / j); 
            }
        }
    }
    vector<int> cnt(m + 1);
    int sz = 0, j = 0;
    int best = 1e5 + 1;
    for(int i = 0; i < n; i++) {
        while(j < n && sz < m) {
            for(int f : fac[j])
                sz += (cnt[f]++) == 0;
            j++;
        }
        if(sz >= m) best = min(best, a[j - 1] - a[i]);
        for(int f : fac[i])
            sz -= (--cnt[f]) == 0;
    }
    cout << ((best == 1e5 + 1) ? -1 : best) << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}