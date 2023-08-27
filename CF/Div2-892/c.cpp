#include <cplib/general.h>
using namespace std;

ll eval(int a, int b) {
    ll ans = 0;
    ll mx = 0;
    for(int i = 1; i <= b; i++) {
        ans += (ll)i * i;
        mx = max(mx, (ll)i * i);
    }
    for(int i = b + 1; i <= a; i++) {
        ans += (ll)i * (a - i + b + 1);
        mx = max(mx, (ll)i * (a - i + b + 1));
    }
    return ans - mx;
}

void tc() {
    int n; rd(n);
    ll best = 0;
    for(int i = 0; i <= n; i++) best = max(best, eval(n, i));
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}