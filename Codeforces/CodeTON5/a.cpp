#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n); rd(m);
    vector<int> a(n); rd(a);
    vector<int> b(m); rd(b);
    ll sma = 0, smb = 0;
    for(int ai : a) sma += ai;
    for(int bi : b) smb += bi;
    if(sma > smb) cout << "Tsondu\n";
    else if(sma == smb) cout << "Draw\n";
    else cout << "Tenzing\n";
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}