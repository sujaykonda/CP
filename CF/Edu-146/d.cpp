#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> f(n); rd(f);
    vector<int> d(n); rd(d);
    vector<ll> p(n);
    for(int i = 0; i < n; i++) p[i] = (ll)f[i] * d[i];
    vector<vector<int>> pcnt(n, vector<int>(k + 1));
    vector<vector<int>> gcnt(n, vector<int>(k + 1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(llabs(p[i] - p[j]) <= k) {
                if(p[i] >= p[j]) {
                    pcnt[j][p[i] - p[j]]++;
                } else {
                    pcnt[j][0]++;
                    pcnt[j][k + 1 + p[i] - p[j]]--;
                }
            }
        }
        for(int j = 0; j < n; j++) {
            if(f[i] > k) {
                int m = p[j] % f[i];
                if(m <= k && m < p[j]) {
                    gcnt[j][0]++;
                    if(m != 0) {
                        gcnt[j][k + 1 - m]--;
                    }
                }
                if(m + k >= f[i]) {
                    gcnt[j][f[i] - m]++;
                }
            } else {
                gcnt[j][max(0ll, f[i] - p[j])]++;
            }
        }
    }

    int best = n;
    for(int i = 0; i < n; i++) {
        int curp = 0, curg = 0;
        for(int j = 0; j <= k; j++) {
            curp += pcnt[i][j];
            curg += gcnt[i][j];
            if(curg == n) {
                best = min(best, n - curp);
            }
        }
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}