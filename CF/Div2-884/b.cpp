#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    if(n == 1) {
        cout << 1 << endl;
    } else if (n == 2) {
        cout << 1 << " " << 2 << endl;
    } else {
        vector<int> p;
        p.pb(2);
        for(int i = 5; i <= n; i += 2) p.pb(i);
        p.pb(1);
        for(int i = 4; i <= n; i += 2) p.pb(i);
        p.pb(3);
        for(int i : p) cout << i << " ";
        cout << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}