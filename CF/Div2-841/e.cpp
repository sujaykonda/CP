#include <cplib/general.h>
using namespace std;

const int MXN = 1e6 + 1;

array<int, MXN> tot;
array<ll, MXN> pairs;

void tc() { 
    int n; ll m; rd(n, m);
    ll x = 0, c = 0;
    for(int i = n / 2 - 1; i >= 1; i--) {
        x += (pairs[n / (i + 1)] / i) * i;
        c += pairs[n / (i + 1)] / i;
        if(x >= m) {
            cout << m + c - ((x - m) / i) << endl;
            return;
        }
    }
    cout << -1 << endl;
}

int main() {
    for(int i = 1; i < MXN; i++) tot[i] = i;
    for(int i = 2; i < MXN; i++)
        if(tot[i] == i)
            for(int j = i; j < MXN; j += i)
                tot[j] -= tot[j] / i;
    
    for(int i = 2; i < MXN; i++) 
        pairs[i] = pairs[i - 1] + tot[i];
    
    int t; rd(t); while(t--) tc();
}