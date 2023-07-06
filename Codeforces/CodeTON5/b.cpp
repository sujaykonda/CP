#include <cplib/general.h>
using namespace std;

void tc() {
    int n, x; rd(n); rd(x);
    int v = 0;
    vector<int> a(n); rd(a);
    vector<int> b(n); rd(b);
    vector<int> c(n); rd(c);
    int i;
    i = 0;
    while((x | a[i]) == x && i < n) v |= a[i++];
    i = 0;
    while((x | b[i]) == x && i < n) v |= b[i++];
    i = 0;
    while((x | c[i]) == x && i < n) v |= c[i++];
    if(x == v) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}