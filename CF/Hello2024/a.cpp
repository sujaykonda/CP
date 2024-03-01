#include <cplib/general.h>
using namespace std;

int main() {
    int t; rd(t);
    while(t--) {
        int a, b; rd(a, b);
        if((a + b) % 2) cout << "Alice" << endl;
        else cout << "Bob" << endl;
    }
}