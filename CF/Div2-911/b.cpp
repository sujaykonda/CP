#include <cplib/general.h>
using namespace std;

int solve(int a, int b, int c) {
    int k = min(b, c);
    a += k, b -= k, c -= k;
    if(max(b, c) % 2 == 0 && a > 0) {
        return true;
    } else {
        return false;
    }
}

void tc() {
    int a, b, c; rd(a, b, c);
    cout << solve(a, b, c) << " " << solve(b, a, c) << " " << solve(c, a, b) << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}