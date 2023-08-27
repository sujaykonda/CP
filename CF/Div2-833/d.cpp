#include <cplib/general.h>
using namespace std;

void tc() {
    int a, b, d; rd(a, b, d);
    ll x = a | b;
    int y = 0;
    while(d % 2 == 0) {
        if(x % 2) {
            cout << "-1" << endl;
            return;
        }
        x >>= 1;
        d >>= 1;
        y++;
    }
    int inv = 1;
    for(int i = 0; i < 30 - y; i++) inv = ((ll) inv * (d + 1) / 2) % d;
    x = ((((ll)((d - (x % d)) % d) * inv) % d) << 30LL) + (x << y);
    cout << x << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}