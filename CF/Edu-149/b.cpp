#include <cplib/general.h>
using namespace std;

void testcase() {
    int n; rd(n);
    string s; rd(s);
    int mxd = 0, mxu = 0;
    int d = 0, u = 0;
    for(char c : s)
        if(c == '<')
            d++, u = 0, mxd = max(d, mxd);
        else
            u++, d = 0, mxu = max(u, mxu);
    cout << max(mxu, mxd) + 1 << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}