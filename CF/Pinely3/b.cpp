#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<ll> a(n); rd(a);
    ll k = 1;
    auto check = [&] () {
        for(ll ai : a) {
            if((ai - a[0]) % k != 0) return true;
        }
        return false;
    };
    while(!check()) k *= 2;
    cout << k << endl;
    
}

int main() {
    int t; rd(t);
    while(t--) tc();
}