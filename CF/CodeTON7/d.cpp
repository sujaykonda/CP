#include <cplib/general.h>
#include <cplib/ds/bit.h>
#include <cplib/ds/segt.h>
#include <cplib/bs.h>
using namespace std;

int segtsm(int a, int b) { return a + b; }
int segtmn(int a, int b) { return min(a, b); }
void tc() {
    int n, q; rd(n, q);
    vector<int> a(n); rd(a);

    SegT<int, segtsm> smq(n);
    for(int i = 0; i < n; i++) smq.mod(i, a[i]);
    SegT<int, segtmn> mnq(n, 2);
    for(int i = 0; i < n; i++) mnq.mod(i, a[i]);

    for(int i = 0; i < q; i++) {
        int op; rd(op);
        if(op == 1) {
            int sm; rd(sm);
            int k = bsmin(0, n - 1, [&] (int x) { return smq.query(0, x) >= sm; });
            if(k == n) {
                cout << "NO" << endl;
            } else {
                if(smq.query(0, k) == sm) {
                    cout << "YES" << endl;
                } else {
                    int first1 = bsmin(0, n - 1, [&] (int x) { return mnq.query(0, x) == 1; });
                    int first1afterk = bsmin(k + 1, n - 1, [&] (int x) { return mnq.query(k + 1, x) == 1; });
                    int s = min(first1 + 1, first1afterk - k);
                    k = bsmin(s, n - 1, [&] (int x) { return smq.query(s, x) >= sm; });
                    if(k == n) {
                        cout << "NO" << endl;
                    } else {
                        if(smq.query(s, k) == sm) {
                            cout << "YES" << endl;
                        } else {
                            cout << "NO" << endl;
                        }
                    }
                }
            }
        } else {
            int k, v; rd(k, v);
            k--;
            smq.mod(k, v);
            mnq.mod(k, v);
        }
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}