#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    vector<bool> done(n + 1);
    for(int i = 0; i < n; i++) done[a[i]] = true;
    int v = 0;
    while(done[v]) v++;
    a.pb(v);
    k = (n + 1 - (k % (n + 1))) % (n + 1);
    for(int i = 0; i < n; i++)
        cout << a[(i + k) % (n + 1)] << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}