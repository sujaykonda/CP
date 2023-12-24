#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n, (1 << 30) - 1);
    vector<vector<int>> M(n, vector<int>(n)); rd(M);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                a[i] &= M[i][j];
                a[j] &= M[i][j];
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                if((a[i] | a[j]) != M[i][j]) {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
    }
    cout << "YES" << endl;
    for(int i : a) cout << i << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}