#include <cplib/general.h>
using namespace std;

int main() {
    int n, m; rd(n, m);
    vector<int> x(n); rd(x);
    sort(x.begin(), x.end());
    int workingk = -1;
    for(int k = 1; k <= n; k++) {
        if(x.end()[-k] > m / k) {
            workingk = k;
            break;
        }
    }
    if(workingk == -1) {
        cout << "Alessia" << endl;
        vector<bool> taken(m + 1);
        for(int i = 1; i <= n; i++) {
            int y = x.end()[-i];
            int a = -1;
            int cnt = 0;
            for(int j = 0; j < y; j++) cnt += taken[j];
            for(int j = 0; j <= m - y; j++) {
                if(cnt == 0) {
                    a = j;
                    break;
                }
                cnt += taken[j + y] - taken[j];
            }
            cout << y << " " << a + 1 << endl;
            int b; rd(b); b--;
            taken[b] = true;
        }
    } else {
        int isz = m / workingk + 1;
        cout << "Bernardo" << endl;
        for(int i = 0; i < n; i++) {
            int y, a; rd(y, a);
            if(isz - (a % isz) >= y) {
                cout << a << endl;
            } else {
                cout << (a / isz + 1) * isz << endl;
            }
        }
    }
}