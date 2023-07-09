#include <cplib/general.h>
using namespace std;

int n, k; ll m;
vector<ll> a;

ll eval(ll L, ll R, ll v) {
    if(L == -1) L = -v - 1;
    if(R == -1) R = m + m - v + 1;
    return (v - L - 1) / 2 + 1 + (R - v - 1) / 2;
}

int main() { 
    rd(n, m, k);
    a.resize(n); rd(a);
    if(n < k) {
        cout << m + 1 << " " << 0 << endl;
    } else {
        sort(a.begin(), a.end());
        ll t = 0, b = 0;
        if(a[0] - 1 >= 0 && b < eval(-1, a[k - 1], a[0] - 1)) b = eval(-1, a[k - 1], a[0] - 1), t = a[0] - 1;
        if(a[0] - 2 >= 0 && b < eval(-1, a[k - 1], a[0] - 2)) b = eval(-1, a[k - 1], a[0] - 2), t = a[0] - 2;
        int cnt = 1;
        for(int i = 0; i < n; i++) {
            if(i + 1 < n && a[i] == a[i + 1]) { cnt++; continue; }
            ll L = -a[i] - 1, R = m + m - a[i] + 1;
            if(i - k + 1 >= 0) L = a[i - k + 1];
            if(i - cnt + k < n) R = a[i - cnt + k];
            ll v = (a[i] - L - 1) / 2 + (cnt < k) + (R - a[i] - 1) / 2;
            if(v > b) b = v, t = a[i];
            cnt = 1;
            if(i + 1 < n && a[i + 1] - a[i] >= 2) {
                ll L = -1, R = -1;
                if(i - k + 1 >= 0) L = a[i - k + 1];
                if(i + k < n) R = a[i + k];
                if(b < eval(L, R, a[i] + 1)) b = eval(L, R, a[i] + 1), t = a[i] + 1;
                if(a[i + 1] - a[i] >= 3) {
                    if(b < eval(L, R, a[i] + 2)) b = eval(L, R, a[i] + 2), t = a[i] + 2;
                    if(b < eval(L, R, a[i + 1] - 2)) b = eval(L, R, a[i + 1] - 2), t = a[i + 1] - 2;
                }
                if(b < eval(L, R, a[i + 1] - 1)) b = eval(L, R, a[i + 1] - 1), t = a[i + 1] - 1;
            }
        }
        if(a[n - 1] + 1 <= m && b < eval(a[n - k], -1, a[n - 1] + 1)) b = eval(a[n - k], -1, a[n - 1] + 1), t = a[n - 1] + 1;
        if(a[n - 1] + 2 <= m && b < eval(a[n - k], -1, a[n - 1] + 2)) b = eval(a[n - k], -1, a[n - 1] + 2), t = a[n - 1] + 2;
        
        cout << b << " " << t << endl;
    }
}