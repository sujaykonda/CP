#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    string s; rd(s);
    int mxw = 0, curw = 0;
    for(int i = 0; i < n; i++) curw += s[i] == 'W';
    for(int i = 0; i < n - 1; i++) {        
        mxw = max(mxw, curw);
        curw += (s[i + n] == 'W') - (s[i] == 'W');
    }
    cout << max(mxw, curw) << endl;
}