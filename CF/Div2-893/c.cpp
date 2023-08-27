#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a;
    vector<int> done(n + 1);
    for(int i = 1; i <= n; i++) {
        if(done[i]) continue;
        int j = i;
        while(j <= n) {
            a.pb(j);
            done[j] = true;
            j *= 2;
        }
    }
    for(int ai : a) cout << ai << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}