#include <cplib/general.h>
using namespace std;
void tc() {
    int n; rd(n);
    int c = 1;
    while(n % c == 0) c++;
    for(int i = 0; i < n; i++) {
        cout << (char)('a' + (i % c));
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}