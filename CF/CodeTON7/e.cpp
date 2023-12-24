#include <cplib/general.h>
#include <cplib/ds/bit.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    BIT bit(2 * n);
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] > i) {
            bit.add(n + a[i], 1);
        }
    }
    vector<int> ans(n);
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] > i) {
            ans[a[i] - 1] = a[i] - i - 1 - bit.sum(a[i]);
            bit.add(a[i], 1);
        } else {
            ans[a[i] - 1] = n + a[i] - i - 1 - bit.sum(n + a[i]);
            bit.add(n + a[i], 1);
        }
    }
    for(int i : ans) cout << i << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}