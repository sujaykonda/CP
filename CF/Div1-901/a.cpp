#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m, k; rd(n, m, k);
    multiset<int> a, b;
    for(int i = 0; i < n; i++) {
        int x; rd(x); a.insert(x);
    }
    for(int i = 0; i < m; i++) {
        int x; rd(x); b.insert(x);
    }
    int i = 1;
    while(i <= 100 && k > 0) {
        int av, bv;
        if(i % 2 == 1) {
            bv = *b.rbegin();
            av = *a.begin();
        } else {
            bv = *b.begin();
            av = *a.rbegin();
        }
        if((bv > av && i % 2 == 1) || (av > bv && i % 2 == 0)) {
            b.erase(b.find(bv));
            a.erase(a.find(av));
            a.insert(bv);
            b.insert(av);
        }
        k--;
        i++;
    }
    if(k % 2 == 1) {
        int bv = *b.rbegin();
        int av = *a.begin();
        b.erase(b.find(bv));
        a.erase(a.find(av));
        a.insert(bv);
        b.insert(av);
    }
    long long sm = 0;
    for(int i : a) sm += i;
    cout << sm << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}