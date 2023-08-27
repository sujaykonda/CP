#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    if(n == 1) {
        cout << "NO" << endl;
        return;
    }
    sort(a.begin(), a.end());
    bool good = false;
    ll sm = 0;
    for(int i = n - 1; i > 0; i--) {
        if(a[i] == 1) break;
        sm += a[i] - 1;
        if(sm >= i) good = true;
    }
    if(good) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}