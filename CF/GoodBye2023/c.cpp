#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    ll sm = 0;
    int oddcnt = 0, evencnt = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] % 2 == 0) evencnt++;
        else oddcnt++;
        sm += a[i];
        if(i == 0) cout << sm << " ";
        else cout << sm - (oddcnt) / 3 - (oddcnt % 3 == 1) << " ";
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}