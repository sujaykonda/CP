#include <cplib/general.h>
using namespace std;

void tc() {
    int a, b; rd(a, b);
    cout << a + b << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}