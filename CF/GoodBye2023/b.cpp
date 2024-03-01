#include <cplib/general.h>
using namespace std;

void tc() {
    int a, b; rd(a, b);
    if(a < b) swap(a, b);
    int g = (ll) a * b / gcd(a, b);
    if(g == a) {
        g *= a / b;
    }
    cout << g << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}