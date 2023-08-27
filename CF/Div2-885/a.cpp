#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m, k; rd(n, m, k);
    int x, y; rd(x, y);
    vector<pair<int, int>> f(k); rd(f);
    for(pair<int, int> p : f) {
        if((p.first + p.second) % 2 == (x + y) % 2) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}