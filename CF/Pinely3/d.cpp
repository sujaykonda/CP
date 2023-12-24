#include <cplib/general.h>
using namespace std;

void tc() {
    
        ll n, k; rd(n, k);
        vector<ll> a(n); rd(a);
        ll g = 0;
        bool allneg = true;
        for(ll ai : a) {
            if(ai - k > 0) allneg = false;
            g = gcd(g, ai - k);
        }
        if(allneg) g = -g;
        if(g == 0) {
            cout << 0 << endl;
            return;
        }
        ll op = 0;
        for(ll ai : a) {
            if((ai - k) / g <= 0) {
                cout << -1 << endl;
                return;
            }
            op += (ai - k) / g - 1;
        }
        cout << op << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}