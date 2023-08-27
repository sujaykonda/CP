#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int mni = 0;
    for(int i = 1; i < n; i++) if(a[i] < a[mni]) mni = i;
    vector<int> b, c;
    for(int i = 0; i < n; i++) 
        if(a[i] == a[mni]) b.pb(a[i]);
        else c.pb(a[i]);
    if(c.size() == 0) cout << -1 << endl;
    else {
        cout << b.size() << " " << c.size() << endl;
        for(int bi : b) cout << bi << " ";
        cout << endl;
        for(int ci : c) cout << ci << " ";
        cout << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}