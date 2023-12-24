#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    if(k == 1) {
        for(int i = 1; i < n; i++) {
            if(a[i] < a[i - 1]) {
                cout << "NO" << endl;
                return;
            }
        }
        cout << "YES" << endl;
    } else {
        cout << "YES" << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}