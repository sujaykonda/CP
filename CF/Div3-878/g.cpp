#include <cplib/general.h>
using namespace std;

const int MXN = 1e6, G = 400, MXG = 1000, JMP_SZ = (MXG - G) / 2;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    int x; rd(x);
    int mx = x;
    for(int i = 1; i < G; i++) {
        cout << "+ " << uniform_int_distribution<int>(1, MXN)(rng) << endl; rd(x);
        mx = max(mx, x);
    }
    array<int, JMP_SZ> ends{};
    for(int i = 0; i < JMP_SZ; i++) {
        cout << "+ 1" << endl; rd(ends[i]);
        if(i > 0 && ends[i] == ends[0]) {
            cout << "! " << i << endl;
            return 0;
        }
    }
    cout << "+ " << mx << endl; rd(x);
    int p = mx;
    while(true) {
        for(int i = 0; i < JMP_SZ; i++) {
            if(ends[i] == x) {
                cout << "! " << JMP_SZ - 1 - i + p << endl;
                return 0;
            }
        }
        cout << "+ " << JMP_SZ << endl; rd(x);
        p += JMP_SZ;
    }
}