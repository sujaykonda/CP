#include <cplib/general.h>
using namespace std;

void tc() {
    int a, b, c;
    rd(a, b, c);
    if(a + (c + 1) / 2 > b + c / 2) {
        cout << "First" << endl;
    } else {
        cout << "Second" << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}