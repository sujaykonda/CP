#include <cplib/general.h>
// the previous include is just my template (rd(i) reads into i)
using namespace std;
const int MAXSQRT = 31623;
int grundy(int x) {
    int xsqrt = 0;
    for(int i = 0; i < MAXSQRT; i++)
        if(i * i > x) {
            xsqrt = i - 1;
            break;
        }
    for(int i = xsqrt; i >= 0; i--) {
        if(i * i < x)
            x -= (x - i * i + i) / (i + 1) * (i + 1);
        if(i * i == x) return i;
    }
    return 0;
}

int game() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int g = 0;
    for(int ai : a)
        g ^= grundy(ai);
    return g == 0;
}

int main() {
    int g; rd(g);
    int ans = 0;
    for(int i = 0; i < g; i++) ans += (game() << i);
    cout << ans << endl;
}
