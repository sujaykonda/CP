#include <cplib/general.h>
using namespace std;
const int MOD = 998244353;
int main() {
    int n, a, x, y, m, k; rd(n, a, x, y, m, k);
    vector<int> b(n); b[0] = a;
    int last = a;
    for(int i = 1; i < n; i++) {
        last = ((ll)last * x + y) % m;
        b[i] = (b[i - 1] + last) % MOD;
    }
    for(int i = 1; i <= k; i++) {
        vector<int> nb(n); nb[0] = a * (i == 1);
        last = a;
        for(int j = 1; j < n; j++) {
            last = ((ll)last * x + y) % m;
            nb[j] = ((ll)nb[j - 1] + b[j - 1] + last * (i == 1)) % MOD;
        }
        b = nb;
    }
    ll c = 0;
    for(int i = 0; i < n; i++) c ^= (ll)b[i] * (i + 1);
    cout << c << endl;
}