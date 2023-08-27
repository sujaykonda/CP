#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int mxi = 0, mni = 0;
    int ncnt = 0, pcnt = 0;
    for(int i = 0; i < n; i++) {
        if(a[mxi] < a[i]) mxi = i;
        if(a[mni] > a[i]) mni = i;
        ncnt += a[i] < 0, pcnt += a[i] > 0;
    }
    vector<pair<int, int>> oper;
    if((a[mxi] > -a[mni] && ncnt <= 12) || (-a[mni] >= a[mxi] && pcnt > 12)) {
        if(-a[mni] > a[mxi] && ncnt <= 7) {
            for(int j = 0; j < 5; j++)
                oper.pb({mxi, mxi});
        }
        for(int i = 0; i < n; i++)
            if(a[i] < 0) oper.pb({i, mxi});
        for(int i = 1; i < n; i++)
            oper.pb({i, i - 1});
    } else {
        if(a[mxi] > -a[mni] && pcnt <= 7) {
            for(int j = 0; j < 5; j++)
                oper.pb({mni, mni});
        }
        for(int i = 0; i < n; i++)
            if(a[i] > 0) oper.pb({i, mni});
        for(int i = n - 2; i >= 0; i--)
            oper.pb({i, i + 1});
    }
    cout << oper.size() << endl;
    for(auto [i, j] : oper) cout << i + 1 << " " << j + 1 << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}