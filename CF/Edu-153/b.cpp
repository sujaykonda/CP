#include <cplib/general.h>
using namespace std;

void tc() {
    int m, k, a, b; 
    rd(m, k, a, b);
    int x = m % k;
    int y = m / k;
    int v = (a - x) / k;
    x += v * k;
    y -= v;
    cout << min(max(0, x - a) + max(0, y - b), max(0, x + k - a) + max(0, y - 1 - b)) << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}