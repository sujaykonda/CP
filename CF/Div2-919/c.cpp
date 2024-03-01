#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int tot = 0;
    for(int k = 1; k <= n; k++) {
        if(n % k == 0) {
            int m = 0;
            for(int i = 0; i < n - k; i++) {
                m = gcd(m, a[i + k] - a[i]);
            }
            tot += m != 1;
        }
    }
    cout << tot << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}