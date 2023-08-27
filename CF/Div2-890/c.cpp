#include <cplib/bs.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    auto F = [&] (int a) {
        return ((ll) a * (a + 1)) / 2;
    };
    int best = 0;
    for(int i = 0; i < n; i++) {
        ll sm = 0;
        int mx = a[i];
        for(int j = i; j < n; j++) {
            if(a[j] + j >= mx) {
                int v = bsmax(mx, a[j] + j, [&] (int x) {
                    return k + sm >= F(x - i) - F(x - j);
                });
                if(v >= mx)
                    best = max(v - i, best);
                mx = a[j] + j;
            }
            sm += a[j];
        }
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}