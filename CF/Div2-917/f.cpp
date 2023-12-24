#include <cplib/general.h>
using namespace std;
const int MX = 2001;

void tc() {
    int n, d; rd(n, d);
    vector<int> l(n); rd(l);
    sort(l.begin(), l.end());
    vector<int> suff(n + 1);
    vector<bitset<MX>> sm(n + 1);
    sm[n][0] = 1;
    suff[n] = 0;
    for(int i = n - 1; i >= 0; i--) {
        sm[i] = sm[i + 1];
        sm[i] |= sm[i] << l[i];
        suff[i] = suff[i + 1] + l[i];
    }
    array<bitset<MX>, MX> cur, nw;
    cur[0][0] = 1;
    for(int i = 0; i < n; i++) {
        nw = cur;
        for(int j = 0; j <= d / 2 - l[i]; j++) {
            nw[j + l[i]] |= cur[j];
        }
        for(int j = 0; j <= d / 2; j++) {
            nw[j] |= cur[j] << l[i];
        }
        cur = nw;
        if(d >= suff[i + 1]) {
            for(int j = 0; j <= (d - suff[i + 1]) / 2; j++) {
                if(cur[j][d - suff[i + 1] - j]) {
                    int a1 = j + sm[i + 1]._Find_next(d / 2 - j - 1);
                    int a2 = d - suff[i + 1] - j + sm[i + 1]._Find_next(max(0, d / 2 - (d - suff[i + 1] - j)) - 1);
                    if(min(a1, d - a1) >= l[i] || min(a2, d - a2) >= l[i]) {
                        cout << "YES" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "NO" << endl;
}
int main() {
    int t; rd(t);
    while(t--) tc();
}