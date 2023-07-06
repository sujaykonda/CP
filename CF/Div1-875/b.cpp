#include <cplib/general.h>
using namespace std;

void testcase() {
    int n; rd(n);
    vector<ll> a(n); rd(a);
    vector<ll> b(n); rd(b);
    ll ans = 0;
    ll ocnt = 0;
    for(int i = 1; i * i <= 2 * n; i++) {
        vector<ll> acnt(n + 1);
        for(int j = 0; j < n; j++)
            if(a[j] == i)
                acnt[b[j]]++;
        for(int j = 0; j < n; j++)
            if(a[j] * i - b[j] <= n && a[j] * i - b[j] >= 1) {
                ans += acnt[a[j] * i - b[j]];
                if(a[j] * a[j] <= 2 * n)
                    ocnt += acnt[a[j] * i - b[j]];
            }
    }
    for(int i = 0; i < n; i++) {
        if(a[i] * a[i] == b[i] + b[i])
            ans--, ocnt--;
    }
    ans -= ocnt / 2;
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}