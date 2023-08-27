#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    int sz = 1;
    vector<int> poss;
    for(int i = 0; i < n; i++) poss.pb(i);
    auto q = [&] (int a, int b) {
        int x = 0, y = 0; 
        cout << "? " << a + 1 << " " << b + 1 << endl;
        rd(x);
        if(b - a > 1) {
            cout << "? " << a + 1 << " " << b << endl;
            rd(y);
        }
        return x != y;
    };
    while(poss.size() > 1) {
        vector<int> nposs;
        for(int i = 0; i < poss.size(); i += 2) {
            if(i + 1 == poss.size()) {
                nposs.pb(poss[i]);
                break;
            }
            if(q(poss[i], poss[i + 1])) {
                nposs.pb(poss[i]);
            } else {
                nposs.pb(poss[i + 1]);
            }
        }
        poss = nposs;
    }
    cout << "! " << poss[0] + 1 << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}