#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll M = 998244353;

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string a, b;
        vector<ll> e(n + 1);
        e[0] = 0;
        e[1] = fe(2, n, M) - 1;
        for(int i = 1; i < n; i++)
            e[i + 1] = (((n * e[i]) % M - n - (i * e[i - 1]) % M) * minv(n - i, M) % M + M) % M;
        cin >> a >> b;
        int d = 0;
        for(int i = 0; i < n; i++) d += a[i] != b[i];
        cout << e[d] << endl;
    }
}