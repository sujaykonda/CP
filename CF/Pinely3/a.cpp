#include <cplib/general.h>
using namespace std;

int main() {
    int t; rd(t);
    while(t--) {
        int n; rd(n);
        int mnx = 101, mny = 101, mxx = -101, mxy = -101;
        for(int i = 0; i < n; i++) {
            int x, y; rd(x, y);
            mnx = min(mnx, x);
            mxx = max(mxx, x);
            mny = min(mny, y);
            mxy = max(mxy, y);
        }
        if(mnx < 0 && 0 < mxx && mny < 0 && 0 < mxy) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
}