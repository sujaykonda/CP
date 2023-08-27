#include <cplib/bs.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    cout << bsmin(0, 1e9 + 1, [&] (int x) { 
        vector<int> b(n);
        for(int i = 0; i < n; i++) b[i] = max(a[i] - x, 0);
        bool so = true;
        for(int i = 1; i < n; i++)  
            so = so && b[i] >= b[i - 1];
        return so;
    }) << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}