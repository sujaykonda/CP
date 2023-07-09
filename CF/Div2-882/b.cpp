#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int base = a[0];
    for(int ai : a) base &= ai;
    if(base != 0) {
        cout << 1 << endl;
    } else {
        int g = 0;
        int cur = a[0];
        for(int i = 0; i < n; i++) {
            cur &= a[i];
            if(cur == 0) {
                g++;
                if(i < n - 1) cur = a[i + 1];
            }
        }
        cout << g << endl;
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}