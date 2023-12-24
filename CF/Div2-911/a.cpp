#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    string s; rd(s);
    int cnt = 0;
    int cur = 0;
    bool three = false;
    for(char c : s) {
        if(c == '.') {
            cur++;
            cnt++;
            if(cur == 3) three = true;
        } else {
            cur = 0;
        }
    }
    if(three) cout << 2 << endl;
    else cout << cnt << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}