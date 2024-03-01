#include <cplib/general.h>
using namespace std;

int main() {
    int t; rd(t);
    while(t--) {
        int n; rd(n);
        string s; rd(s);
        int v = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '+') v++;
            else v--;
        }
        cout << abs(v) << endl;
    }
}