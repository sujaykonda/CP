#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
const int MXN = 1e5 + 1;

int main() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    if(n == 1) {
        cout << a[0] << endl;
        return 0;
    }
    bitset<MXN> shift, res; shift[0] = 1;
    int ex = n + 1;
    for(int i = 0; i < n - 1; i++) {
        int nxt = shift._Find_next(max(-1, n - 2 - a[i]));
        if(nxt < MXN)
            ex = min(ex, nxt - (n - 1 - a[i])); 
        shift |= shift << a[i];
        res[i] = shift[i];
        shift[i] = 0;
    }
    ll sm = 0, best = 0;
    for(int i = 0; i < n - 1; i++) {
        sm += a[i];
        if(res[i])
            best = max(best, sm - i);
    }
    sm += a[n - 1];
    if(ex <= n)
        best = max(best, sm - (n - 1 + ex));
    cout << best << endl;
}