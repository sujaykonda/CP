#include <cplib/general.h>
using namespace std;

void testcase() {
    int n; rd(n);
    string s; rd(s);
    vector<int> c(n);
    int v = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') v++;
        else if(s[i] == ')') v--;
        if(v > 0) c[i] = 1;
        else if(v < 0) c[i] = 2;
    }
    if(v != 0) { cout << -1 << endl; return; }
    bool all1 = true;
    for(int i = 0; i < n; i++)
        if(c[i] == 2) all1 = false;
    bool all2 = true;
    for(int i = 0; i < n; i++)
        if(c[i] == 1) all2 = false;
    if(all1 || all2) {
        cout << 1 << endl;
        for(int i = 0; i < n; i++)
            cout << 1 << " ";
        cout << endl;
    } else {
        cout << 2 << endl;
        for(int i = 0; i < n; i++)
            cout << (c[i] == 0 ? c[i - 1] : c[i]) << " ";
        cout << endl;
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}