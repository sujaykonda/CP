#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    ll m = 0, best = 0;
    ll sm = 0;
    for(int i = 0; i < n; i++) sm += a[i];
    
    ll suff = 0;
    ll mxsuff = 0;
    if(sm > best) best = sm, m = sm;
    for(int i = n - 1; i >= 0; i--) {
        suff += a[i];
        mxsuff = max(mxsuff, suff);
        sm -= a[i];
        if(sm + mxsuff > best) {
            m = sm;
            best = sm + mxsuff;
        }
    }
    cout << m << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}