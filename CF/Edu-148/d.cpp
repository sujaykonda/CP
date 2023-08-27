#include <cplib/general.h>
using namespace std;

int main() {
    int n, q; rd(n, q);
    vector<int> a(n), k(q); rd(a, k);
    sort(a.begin(), a.end());
    vector<int> special(n);
    int mn = a[0];
    for(int i = 1; i < n; i++) {
        special[i] = min(mn + i, a[i]);
        mn = min(a[i] - i, mn);
    }
    vector<int> b = a;
    for(int i = 0; i < n; i++) b[i] += n - i;
    sort(b.begin(), b.end());
    ll sm = 0;
    for(int i = 1; i < n; i++) sm += b[i] - b[0];
    vector<int> c = a; c.pop_back();
    for(int i = 0; i < n - 1; i++) c[i] += n - 1 - i;
    sort(c.begin(), c.end());
    ll sm2 = 0;
    for(int i = 1; i < n - 1; i++) sm2 += c[i] - c[0];

    vector<ll> ans(q);
    for(int i = 0; i < q; i++) {
        if(k[i] >= n) {
            if((k[i] - n) % 2 == 0) {
                ans[i] = b[0] + k[i] - n;
                if((k[i] - n) / 2 > sm)
                    ans[i] -= ((k[i] - n) / 2 - sm + n - 1) / n;
            } else {
                ll sm3 = sm2 + a[n - 1] - (c[0] + k[i] - n + 1);
                if(a[n - 1] < (c[0] + k[i] - n + 1)) {
                    sm3 = sm2 + (ll)(n - 1) * (c[0] + k[i] - n + 1 - a[n - 1]);
                }
                ans[i] = min(c[0] + k[i] - n + 1, a[n - 1]);
                if((k[i] - n + 1) / 2 > sm3)
                    ans[i] -= ((k[i] - n + 1) / 2 - sm3 + n - 1) / n;
            }
        } else {
            ans[i] = special[k[i]];
        }
    }

    for(int i : ans) cout << i << " ";
    cout << endl;
}