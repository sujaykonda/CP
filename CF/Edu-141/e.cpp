#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n), b(n); rd(a, b);
    vector<int> d(n + 1);
    for(int i = 0; i < n; i++) {
        for(int j = 1; j * j <= (a[i] - 1); j++) {
            if((a[i] - 1) / j <= (b[i] - 1) / j)
                d[j - 1]++, d[j]--;
            if((a[i] - 1) / j != j) {
                int L = (a[i] - 1) / (j + 1) + 1;
                int R = min((a[i] - 1) / j, (b[i] - 1) / j);
                if(L <= R) d[L - 1]++, d[R]--;
            }
        }
        d[a[i] - 1]++, d[n]--;
    }
    vector<int> ans;
    int sm = 0;
    for(int i = 0; i <= n; i++) {
        if(sm == n) ans.pb(i);
        sm += d[i];
    }
    cout << ans.size() << endl;
    for(int ai : ans) cout << ai << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}