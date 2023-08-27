#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    vector<int> ops;
    auto G = [&] (int l, int r) {
        int s = (r - l + n) % n;
        for(int i = s - 1; i >= 0; i--) {
            ops.pb((i + l) % n);
        }
    };
    auto Gp = [&] (int l, int r) {
        int s = (r - l + n) % n;
        for(int i = 0; i < s; i++) {
            ops.pb((i + l) % n);
        }
    };
    auto F = [&] (int l, int r) {
        int s = (r - l + n) % n;
        if(s >= 2) G(l, r);
        for(int i = 0; i < s / 2; i++) {
            // G(l + i, r - i);
            Gp(l + i + 1, r - i);
            G(l + i + 1, r - i - 1);
            ops.pb((i + l) % n);
            // Gp(l + i + 1, r - i - 1);
        }
        if(s >= 2) G(l + s / 2, r - s / 2);
        if(s % 2 == 1)
            ops.pb((s / 2 + l) % n);

    };
    F(0, n - 1);
    if(n % 2 == 0) F(n / 2, n / 2 - 1);
    else F((n + 1) / 2, n / 2 - 1);
    F(0, n - 1);
    cout << ops.size() << endl;
    for(int op : ops) cout << op << " ";
    cout << endl;
    // vector<int> a(n);
    // for(int i = 0; i < n; i++) a[i] = (1 << i);
    // cout << str(a) << endl;
    // for(int op : ops) {
    //     a[op] = a[op] ^ a[(op + 1) % n];
    // }
    // cout << str(a) << endl;
}