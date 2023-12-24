#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    string s; rd(s);
    int lastA = -1;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'A' && lastA == -1) lastA = i;
        if(s[i] == 'B' && lastA != -1) {
            ans += i - lastA;
            lastA = i;
        }
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}