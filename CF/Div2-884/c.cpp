#include <cplib/general.h>
using namespace std;
void tc() {
    int n; rd(n);
    vector<int> c(n); rd(c);
    ll sm1 = 0, sm2 = 0;
    for(int i = 0; i < n; i += 2)
        sm1 += (c[i] > 0) * c[i];
    for(int i = 1; i < n; i += 2)
        sm2 += (c[i] > 0) * c[i];
    if(max(sm1, sm2) == 0) {
        int mx = c[0];
        for(int i = 0; i < n; i++) mx = max(mx, c[i]);
        cout << mx << endl;
    } else {
        cout << max(sm1, sm2) << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}