#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/general.h>

using namespace std;

int main() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int cxor = 0;
    for(int ai : a) cxor ^= ai;
    if(cxor != 0) {
        cout << n << endl;
        return 0;
    }
    int cur = n - 1;
    int lgn = 0; while((1 << (lgn + 1)) <= n) lgn++;
    for(int i = lgn - 1; i >= 0; i--) {
        vector<int> b = a, c(n);
        for(int j = 0; j < i; j++) {
            if(getbit(cur, j)) {
                for(int k = 0; k < n; k++)
                    c[k] = b[k] ^ b[(k + (1 << j)) % n];
                b = c;
            }
        }
        bool good = true;
        for(int k = 0; k < n; k++)
            good &= b[k] == 0;
        if(good)
            cur ^= (1 << i);
        else {
            vector<int> oa = a;
            for(int k = 0; k < n; k++) 
                a[k] = oa[k] ^ oa[(k + (1 << i)) % n];
        }
    }
    cout << cur << '\n';
}