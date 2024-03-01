#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> nt;
    int l = 1, r = 1e9;
    while(n--) {
        int a, x; rd(a, x);
        if(a == 1) l = max(l, x);
        else if(a == 2) r = min(r, x);
        else nt.pb(x);
    }
    int cnt = 0;
    for(int x : nt) if(l <= x && x <= r) cnt++;
    cout << max(0, r - l + 1 - cnt) << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}